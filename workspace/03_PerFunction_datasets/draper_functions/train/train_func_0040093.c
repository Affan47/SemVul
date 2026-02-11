vce_v3_0_process_interrupt(struct amdgpu_device *adev,
				      struct amdgpu_irq_src *source,
				      struct amdgpu_iv_entry *entry)
{
	DRM_DEBUG("IH: VCE\n");

	WREG32_P(mmVCE_SYS_INT_STATUS,
		VCE_SYS_INT_STATUS__VCE_SYS_INT_TRAP_INTERRUPT_INT_MASK,
		~VCE_SYS_INT_STATUS__VCE_SYS_INT_TRAP_INTERRUPT_INT_MASK);

	switch (entry->src_data) {
	case 0:
		amdgpu_fence_process(&adev->vce.ring[0]);
		break;
	case 1:
		amdgpu_fence_process(&adev->vce.ring[1]);
		break;
	default:
		DRM_ERROR("Unhandled interrupt: %d %d\n",
			  entry->src_id, entry->src_data);
		break;
	}

	return 0;
}
