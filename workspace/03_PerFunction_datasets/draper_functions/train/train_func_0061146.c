kimage_alloc_crash_control_pages(struct kimage *image,
						      unsigned int order)
{


	unsigned long hole_start, hole_end, size;
	struct page *pages;

	pages = NULL;
	size = (1 << order) << PAGE_SHIFT;
	hole_start = (image->control_page + (size - 1)) & ~(size - 1);
	hole_end   = hole_start + size - 1;
	while (hole_end <= crashk_res.end) {
		unsigned long i;

		if (hole_end > KEXEC_CRASH_CONTROL_MEMORY_LIMIT)
			break;

		for (i = 0; i < image->nr_segments; i++) {
			unsigned long mstart, mend;

			mstart = image->segment[i].mem;
			mend   = mstart + image->segment[i].memsz - 1;
			if ((hole_end >= mstart) && (hole_start <= mend)) {

				hole_start = (mend + (size - 1)) & ~(size - 1);
				hole_end   = hole_start + size - 1;
				break;
			}
		}

		if (i == image->nr_segments) {
			pages = pfn_to_page(hole_start >> PAGE_SHIFT);
			image->control_page = hole_end;
			break;
		}
	}

	return pages;
}
