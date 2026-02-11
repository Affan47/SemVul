index_mm_open(struct kmod_ctx *ctx, const char *filename,
						unsigned long long *stamp)
{
	int fd;
	struct stat st;
	struct index_mm *idx;
	struct {
		uint32_t magic;
		uint32_t version;
		uint32_t root_offset;
	} hdr;
	void *p;

	DBG(ctx, "file=%s\n", filename);

	idx = malloc(sizeof(*idx));
	if (idx == NULL) {
		ERR(ctx, "malloc: %m\n");
		return NULL;
	}

	if ((fd = open(filename, O_RDONLY|O_CLOEXEC)) < 0) {
		DBG(ctx, "open(%s, O_RDONLY|O_CLOEXEC): %m\n", filename);
		goto fail_open;
	}

	fstat(fd, &st);
	if ((size_t) st.st_size < sizeof(hdr))
		goto fail_nommap;

	if ((idx->mm = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
							== MAP_FAILED) {
		ERR(ctx, "mmap(NULL, %"PRIu64", PROT_READ, %d, MAP_PRIVATE, 0): %m\n",
							st.st_size, fd);
		goto fail_nommap;
	}

	p = idx->mm;
	hdr.magic = read_long_mm(&p);
	hdr.version = read_long_mm(&p);
	hdr.root_offset = read_long_mm(&p);

	if (hdr.magic != INDEX_MAGIC) {
		ERR(ctx, "magic check fail: %x instead of %x\n", hdr.magic,
								INDEX_MAGIC);
		goto fail;
	}

	if (hdr.version >> 16 != INDEX_VERSION_MAJOR) {
		ERR(ctx, "major version check fail: %u instead of %u\n",
						hdr.version, INDEX_MAGIC);
		goto fail;
	}

	idx->root_offset = hdr.root_offset;
	idx->size = st.st_size;
	idx->ctx = ctx;
	close(fd);

	*stamp = stat_mstamp(&st);

	return idx;

fail:
	munmap(idx->mm, st.st_size);
fail_nommap:
	close(fd);
fail_open:
	free(idx);
	return NULL;
}
