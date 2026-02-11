test1(void)
{
	int ret;
	drm_intel_bo *test_intel_bo;
	int prime_fd;
	struct nouveau_bo *nvbo;

	test_intel_bo = drm_intel_bo_alloc(bufmgr, "test bo", BO_SIZE, 4096);

	drm_intel_bo_gem_export_to_prime(test_intel_bo, &prime_fd);

	ret = nouveau_bo_prime_handle_ref(ndev, prime_fd, &nvbo);
	close(prime_fd);
	if (ret < 0)
		return ret;

	nouveau_bo_ref(NULL, &nvbo);
	drm_intel_bo_unreference(test_intel_bo);
	return 0;
}
