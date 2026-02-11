r300_fini(struct radeon_device *rdev)
{
	radeon_pm_fini(rdev);
	r100_cp_fini(rdev);
	radeon_wb_fini(rdev);
	radeon_ib_pool_fini(rdev);
	radeon_gem_fini(rdev);
	if (rdev->flags & RADEON_IS_PCIE)
		rv370_pcie_gart_fini(rdev);
	if (rdev->flags & RADEON_IS_PCI)
		r100_pci_gart_fini(rdev);
	radeon_agp_fini(rdev);
	radeon_irq_kms_fini(rdev);
	radeon_fence_driver_fini(rdev);
	radeon_bo_fini(rdev);
	radeon_atombios_fini(rdev);
	kfree(rdev->bios);
	rdev->bios = NULL;
}
