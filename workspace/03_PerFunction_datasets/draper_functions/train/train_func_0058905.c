amdgpu_uvd_cs_msg(struct amdgpu_uvd_cs_ctx *ctx,
			     struct amdgpu_bo *bo, unsigned offset)
{
	struct amdgpu_device *adev = ctx->parser->adev;
	int32_t *msg, msg_type, handle;
	void *ptr;
	long r;
	int i;

	if (offset & 0x3F) {
		DRM_ERROR("UVD messages must be 64 byte aligned!\n");
		return -EINVAL;
	}

	r = reservation_object_wait_timeout_rcu(bo->tbo.resv, true, false,
						MAX_SCHEDULE_TIMEOUT);
	if (r < 0) {
		DRM_ERROR("Failed waiting for UVD message (%ld)!\n", r);
		return r;
	}

	r = amdgpu_bo_kmap(bo, &ptr);
	if (r) {
		DRM_ERROR("Failed mapping the UVD message (%ld)!\n", r);
		return r;
	}

	msg = ptr + offset;

	msg_type = msg[1];
	handle = msg[2];

	if (handle == 0) {
		DRM_ERROR("Invalid UVD handle!\n");
		return -EINVAL;
	}

	switch (msg_type) {
	case 0:

		amdgpu_bo_kunmap(bo);


		for (i = 0; i < AMDGPU_MAX_UVD_HANDLES; ++i) {
			if (atomic_read(&adev->uvd.handles[i]) == handle) {
				DRM_ERROR("Handle 0x%x already in use!\n", handle);
				return -EINVAL;
			}

			if (!atomic_cmpxchg(&adev->uvd.handles[i], 0, handle)) {
				adev->uvd.filp[i] = ctx->parser->filp;
				return 0;
			}
		}

		DRM_ERROR("No more free UVD handles!\n");
		return -EINVAL;

	case 1:

		r = amdgpu_uvd_cs_msg_decode(msg, ctx->buf_sizes);
		amdgpu_bo_kunmap(bo);
		if (r)
			return r;


		for (i = 0; i < AMDGPU_MAX_UVD_HANDLES; ++i) {
			if (atomic_read(&adev->uvd.handles[i]) == handle) {
				if (adev->uvd.filp[i] != ctx->parser->filp) {
					DRM_ERROR("UVD handle collision detected!\n");
					return -EINVAL;
				}
				return 0;
			}
		}

		DRM_ERROR("Invalid UVD handle 0x%x!\n", handle);
		return -ENOENT;

	case 2:

		for (i = 0; i < AMDGPU_MAX_UVD_HANDLES; ++i)
			atomic_cmpxchg(&adev->uvd.handles[i], handle, 0);
		amdgpu_bo_kunmap(bo);
		return 0;

	default:
		DRM_ERROR("Illegal UVD message type (%d)!\n", msg_type);
		return -EINVAL;
	}
	BUG();
	return -EINVAL;
}
