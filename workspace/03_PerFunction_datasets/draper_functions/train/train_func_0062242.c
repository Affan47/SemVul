si_init_pg(struct radeon_device *rdev)
{
	if (rdev->pg_flags) {
		if (rdev->pg_flags & RADEON_PG_SUPPORT_SDMA) {
			si_init_dma_pg(rdev);
		}
		si_init_ao_cu_mask(rdev);
		if (rdev->pg_flags & RADEON_PG_SUPPORT_GFX_PG) {
			si_init_gfx_cgpg(rdev);
		} else {
			WREG32(RLC_SAVE_AND_RESTORE_BASE, rdev->rlc.save_restore_gpu_addr >> 8);
			WREG32(RLC_CLEAR_STATE_RESTORE_BASE, rdev->rlc.clear_state_gpu_addr >> 8);
		}
		si_enable_dma_pg(rdev, true);
		si_enable_gfx_cgpg(rdev, true);
	} else {
		WREG32(RLC_SAVE_AND_RESTORE_BASE, rdev->rlc.save_restore_gpu_addr >> 8);
		WREG32(RLC_CLEAR_STATE_RESTORE_BASE, rdev->rlc.clear_state_gpu_addr >> 8);
	}
}
