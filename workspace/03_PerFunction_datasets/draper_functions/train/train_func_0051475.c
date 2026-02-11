si_suspend(struct radeon_device *rdev)
{
	radeon_pm_suspend(rdev);
	radeon_audio_fini(rdev);
	radeon_vm_manager_fini(rdev);
	si_cp_enable(rdev, false);
	cayman_dma_stop(rdev);
	if (rdev->has_uvd) {
		uvd_v1_0_fini(rdev);
		radeon_uvd_suspend(rdev);
		radeon_vce_suspend(rdev);
	}
	si_fini_pg(rdev);
	si_fini_cg(rdev);
	si_irq_suspend(rdev);
	radeon_wb_disable(rdev);
	si_pcie_gart_disable(rdev);
	return 0;
}
