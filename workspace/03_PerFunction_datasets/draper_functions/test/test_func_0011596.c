amdgpu_ttm_global_fini(struct amdgpu_device *adev)
{
	if (adev->mman.mem_global_referenced) {
		drm_global_item_unref(&adev->mman.bo_global_ref.ref);
		drm_global_item_unref(&adev->mman.mem_global_ref);
		adev->mman.mem_global_referenced = false;
	}
}
