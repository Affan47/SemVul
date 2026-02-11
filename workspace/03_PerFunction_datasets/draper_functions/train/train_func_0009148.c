vce_v2_0_set_interrupt_state(struct amdgpu_device *adev,
					struct amdgpu_irq_src *source,
					unsigned type,
					enum amdgpu_interrupt_state state)
{
	uint32_t val = 0;

	if (state == AMDGPU_IRQ_STATE_ENABLE)
		val |= VCE_SYS_INT_EN__VCE_SYS_INT_TRAP_INTERRUPT_EN_MASK;

	WREG32_P(mmVCE_SYS_INT_EN, val, ~VCE_SYS_INT_EN__VCE_SYS_INT_TRAP_INTERRUPT_EN_MASK);
	return 0;
}
