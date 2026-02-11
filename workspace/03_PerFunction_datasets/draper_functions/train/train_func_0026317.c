radeon_gart_init(struct radeon_device *rdev)
{
	int r, i;

	if (rdev->gart.pages) {
		return 0;
	}

	if (PAGE_SIZE < RADEON_GPU_PAGE_SIZE) {
		DRM_ERROR("Page size is smaller than GPU page size!\n");
		return -EINVAL;
	}
	r = radeon_dummy_page_init(rdev);
	if (r)
		return r;

	rdev->gart.num_cpu_pages = rdev->mc.gtt_size / PAGE_SIZE;
	rdev->gart.num_gpu_pages = rdev->mc.gtt_size / RADEON_GPU_PAGE_SIZE;
	DRM_INFO("GART: num cpu pages %u, num gpu pages %u\n",
		 rdev->gart.num_cpu_pages, rdev->gart.num_gpu_pages);

	rdev->gart.pages = vzalloc(sizeof(void *) * rdev->gart.num_cpu_pages);
	if (rdev->gart.pages == NULL) {
		radeon_gart_fini(rdev);
		return -ENOMEM;
	}
	rdev->gart.pages_entry = vmalloc(sizeof(uint64_t) *
					 rdev->gart.num_gpu_pages);
	if (rdev->gart.pages_entry == NULL) {
		radeon_gart_fini(rdev);
		return -ENOMEM;
	}

	for (i = 0; i < rdev->gart.num_gpu_pages; i++)
		rdev->gart.pages_entry[i] = rdev->dummy_page.entry;
	return 0;
}
