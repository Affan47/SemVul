amdgpu_cs_dependencies(struct amdgpu_device *adev,
				  struct amdgpu_cs_parser *p)
{
	struct amdgpu_fpriv *fpriv = p->filp->driver_priv;
	struct amdgpu_ib *ib;
	int i, j, r;

	if (!p->num_ibs)
		return 0;


	ib = &p->ibs[0];
	for (i = 0; i < p->nchunks; ++i) {
		struct drm_amdgpu_cs_chunk_dep *deps;
		struct amdgpu_cs_chunk *chunk;
		unsigned num_deps;

		chunk = &p->chunks[i];

		if (chunk->chunk_id != AMDGPU_CHUNK_ID_DEPENDENCIES)
			continue;

		deps = (struct drm_amdgpu_cs_chunk_dep *)chunk->kdata;
		num_deps = chunk->length_dw * 4 /
			sizeof(struct drm_amdgpu_cs_chunk_dep);

		for (j = 0; j < num_deps; ++j) {
			struct amdgpu_ring *ring;
			struct amdgpu_ctx *ctx;
			struct fence *fence;

			r = amdgpu_cs_get_ring(adev, deps[j].ip_type,
					       deps[j].ip_instance,
					       deps[j].ring, &ring);
			if (r)
				return r;

			ctx = amdgpu_ctx_get(fpriv, deps[j].ctx_id);
			if (ctx == NULL)
				return -EINVAL;

			fence = amdgpu_ctx_get_fence(ctx, ring,
						     deps[j].handle);
			if (IS_ERR(fence)) {
				r = PTR_ERR(fence);
				amdgpu_ctx_put(ctx);
				return r;

			} else if (fence) {
				r = amdgpu_sync_fence(adev, &ib->sync, fence);
				fence_put(fence);
				amdgpu_ctx_put(ctx);
				if (r)
					return r;
			}
		}
	}

	return 0;
}
