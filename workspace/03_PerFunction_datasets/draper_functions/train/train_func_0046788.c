omalloc_allocate(size_t size, size_t align, enum omalloc_mode mode,
	const void *init)
{
	struct ochunk *ck;
	void *p;
	size_t allocated;
	static spinlock_t omalloc_slk = SPINLOCK_INIT;

	g_assert(size_is_positive(size));

	if G_UNLIKELY(0 == omalloc_pagesize)
		omalloc_pagesize = compat_pagesize();


	spinlock_hidden(&omalloc_slk);

	if (OMALLOC_RW == mode) {
		ostats.objects_rw++;
	} else {
		ostats.objects_ro++;
	}


	ck = omalloc_chunk_find(size, align, mode);
	if (ck != NULL) {
		p = omalloc_chunk_allocate_from(ck, size, align, mode);
		goto done;
	}


	spinunlock_hidden(&omalloc_slk);

	p = vmm_core_alloc(size);
	allocated = round_pagesize(size);

	if (omalloc_debug > 2) {
		size_t pages = allocated / omalloc_pagesize;
		size_t count = OMALLOC_RW == mode ?
			ostats.objects_rw : ostats.objects_ro;
		s_debug("OMALLOC allocated %zu page%s (%zu total for %zu %s object%s)",
			pages, 1 == pages ? "" : "s",
			OMALLOC_RW == mode ? ostats.pages_rw : ostats.pages_ro,
			count, OMALLOC_RW == mode ? "read-write" : "read-only",
			1 == count ? "" : "s");
	}


	spinlock_hidden(&omalloc_slk);

	if (OMALLOC_RW == mode) {
		ostats.pages_rw += allocated / omalloc_pagesize;
	} else {
		ostats.pages_ro += allocated / omalloc_pagesize;
	}


	if (allocated - size >= OMALLOC_HEADER_SIZE) {
		void *end = ptr_add_offset(p, allocated);
		ck = ptr_add_offset(end, -OMALLOC_HEADER_SIZE);
		ck->first = ptr_add_offset(p, size);
		omalloc_chunk_link(ck, mode);

		if (OMALLOC_RW == mode) {
			ostats.chunks_rw++;
			ostats.memory_rw += size;
		} else {
			ostats.chunks_ro++;
			ostats.memory_ro += size;
		}

		if (omalloc_debug > 2) {
			size_t count = OMALLOC_RW == mode ?
				ostats.chunks_rw : ostats.chunks_ro;
			s_debug("OMALLOC adding %zu byte-long chunk (%zu %s chunk%s total)",
				omalloc_chunk_size(ck),
				count, OMALLOC_RW == mode ? "read-write" : "read-only",
				1 == count ? "" : "s");
		}
	} else {


		if (OMALLOC_RW == mode) {
			ostats.memory_rw += allocated;
		} else {
			ostats.memory_ro += allocated;
		}

		if (allocated != size) {
			if (omalloc_debug > 2) {
				s_debug("OMALLOC %zu trailing bytes lost on "
					"%zu-byte allocation", allocated - size, size);
			}
			if (OMALLOC_RW == mode) {
				ostats.wasted_rw += allocated - size;
			} else {
				ostats.wasted_ro += allocated - size;
			}
		}
	}

done:
	spinunlock_hidden(&omalloc_slk);

	if (init != NULL)
		memcpy(p, init, size);


	omalloc_range_protect(p, mode, size);

	return p;
}
