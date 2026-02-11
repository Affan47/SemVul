amdgpu_uvd_free_handles(struct amdgpu_device *adev, struct drm_file *filp)
{
	struct amdgpu_ring *ring = &adev->uvd.ring;
	int i, r;

	for (i = 0; i < AMDGPU_MAX_UVD_HANDLES; ++i) {
		uint32_t handle = atomic_read(&adev->uvd.handles[i]);
		if (handle != 0 && adev->uvd.filp[i] == filp) {
			struct fence *fence;

			amdgpu_uvd_note_usage(adev);

			r = amdgpu_uvd_get_destroy_msg(ring, handle, &fence);
			if (r) {
				DRM_ERROR("Error destroying UVD (%d)!\n", r);
				continue;
			}

			fence_wait(fence, false);
			fence_put(fence);

			adev->uvd.filp[i] = NULL;
			atomic_set(&adev->uvd.handles[i], 0);
		}
	}
}
