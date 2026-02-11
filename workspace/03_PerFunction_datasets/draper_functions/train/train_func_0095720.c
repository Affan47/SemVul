radeon_uvd_free_handles(struct radeon_device *rdev, struct drm_file *filp)
{
	int i, r;
	for (i = 0; i < RADEON_MAX_UVD_HANDLES; ++i) {
		uint32_t handle = atomic_read(&rdev->uvd.handles[i]);
		if (handle != 0 && rdev->uvd.filp[i] == filp) {
			struct radeon_fence *fence;

			radeon_uvd_note_usage(rdev);

			r = radeon_uvd_get_destroy_msg(rdev,
				R600_RING_TYPE_UVD_INDEX, handle, &fence);
			if (r) {
				DRM_ERROR("Error destroying UVD (%d)!\n", r);
				continue;
			}

			radeon_fence_wait(fence, false);
			radeon_fence_unref(&fence);

			rdev->uvd.filp[i] = NULL;
			atomic_set(&rdev->uvd.handles[i], 0);
		}
	}
}
