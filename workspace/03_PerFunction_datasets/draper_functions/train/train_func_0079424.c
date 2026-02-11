radeon_benchmark_move(struct radeon_device *rdev, unsigned size,
				  unsigned sdomain, unsigned ddomain)
{
	struct radeon_bo *dobj = NULL;
	struct radeon_bo *sobj = NULL;
	uint64_t saddr, daddr;
	int r, n;
	int time;

	n = RADEON_BENCHMARK_ITERATIONS;
	r = radeon_bo_create(rdev, size, PAGE_SIZE, true, sdomain, 0, NULL, NULL, &sobj);
	if (r) {
		goto out_cleanup;
	}
	r = radeon_bo_reserve(sobj, false);
	if (unlikely(r != 0))
		goto out_cleanup;
	r = radeon_bo_pin(sobj, sdomain, &saddr);
	radeon_bo_unreserve(sobj);
	if (r) {
		goto out_cleanup;
	}
	r = radeon_bo_create(rdev, size, PAGE_SIZE, true, ddomain, 0, NULL, NULL, &dobj);
	if (r) {
		goto out_cleanup;
	}
	r = radeon_bo_reserve(dobj, false);
	if (unlikely(r != 0))
		goto out_cleanup;
	r = radeon_bo_pin(dobj, ddomain, &daddr);
	radeon_bo_unreserve(dobj);
	if (r) {
		goto out_cleanup;
	}

	if (rdev->asic->copy.dma) {
		time = radeon_benchmark_do_move(rdev, size, saddr, daddr,
						RADEON_BENCHMARK_COPY_DMA, n,
						dobj->tbo.resv);
		if (time < 0)
			goto out_cleanup;
		if (time > 0)
			radeon_benchmark_log_results(n, size, time,
						     sdomain, ddomain, "dma");
	}

	if (rdev->asic->copy.blit) {
		time = radeon_benchmark_do_move(rdev, size, saddr, daddr,
						RADEON_BENCHMARK_COPY_BLIT, n,
						dobj->tbo.resv);
		if (time < 0)
			goto out_cleanup;
		if (time > 0)
			radeon_benchmark_log_results(n, size, time,
						     sdomain, ddomain, "blit");
	}

out_cleanup:
	if (sobj) {
		r = radeon_bo_reserve(sobj, false);
		if (likely(r == 0)) {
			radeon_bo_unpin(sobj);
			radeon_bo_unreserve(sobj);
		}
		radeon_bo_unref(&sobj);
	}
	if (dobj) {
		r = radeon_bo_reserve(dobj, false);
		if (likely(r == 0)) {
			radeon_bo_unpin(dobj);
			radeon_bo_unreserve(dobj);
		}
		radeon_bo_unref(&dobj);
	}

	if (r) {
		DRM_ERROR("Error while benchmarking BO move.\n");
	}
}
