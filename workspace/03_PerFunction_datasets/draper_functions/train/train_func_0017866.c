amdgpu_cgs_gpu_mem_info(void *cgs_device, enum cgs_gpu_mem_type type,
				   uint64_t *mc_start, uint64_t *mc_size,
				   uint64_t *mem_size)
{
	CGS_FUNC_ADEV;
	switch(type) {
	case CGS_GPU_MEM_TYPE__VISIBLE_CONTIG_FB:
	case CGS_GPU_MEM_TYPE__VISIBLE_FB:
		*mc_start = 0;
		*mc_size = adev->mc.visible_vram_size;
		*mem_size = adev->mc.visible_vram_size - adev->vram_pin_size;
		break;
	case CGS_GPU_MEM_TYPE__INVISIBLE_CONTIG_FB:
	case CGS_GPU_MEM_TYPE__INVISIBLE_FB:
		*mc_start = adev->mc.visible_vram_size;
		*mc_size = adev->mc.real_vram_size - adev->mc.visible_vram_size;
		*mem_size = *mc_size;
		break;
	case CGS_GPU_MEM_TYPE__GART_CACHEABLE:
	case CGS_GPU_MEM_TYPE__GART_WRITECOMBINE:
		*mc_start = adev->mc.gtt_start;
		*mc_size = adev->mc.gtt_size;
		*mem_size = adev->mc.gtt_size - adev->gart_pin_size;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
