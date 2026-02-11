r300_init(struct radeon_device *rdev)
{
	int r;


	r100_vga_render_disable(rdev);

	radeon_scratch_init(rdev);

	radeon_surface_init(rdev);


	r100_restore_sanity(rdev);

	if (!radeon_get_bios(rdev)) {
		if (ASIC_IS_AVIVO(rdev))
			return -EINVAL;
	}
	if (rdev->is_atom_bios) {
		dev_err(rdev->dev, "Expecting combios for RS400/RS480 GPU\n");
		return -EINVAL;
	} else {
		r = radeon_combios_init(rdev);
		if (r)
			return r;
	}

	if (radeon_asic_reset(rdev)) {
		dev_warn(rdev->dev,
			"GPU reset failed ! (0xE40=0x%08X, 0x7C0=0x%08X)\n",
			RREG32(R_000E40_RBBM_STATUS),
			RREG32(R_0007C0_CP_STAT));
	}

	if (radeon_boot_test_post_card(rdev) == false)
		return -EINVAL;

	r300_errata(rdev);

	radeon_get_clock_info(rdev->ddev);

	if (rdev->flags & RADEON_IS_AGP) {
		r = radeon_agp_init(rdev);
		if (r) {
			radeon_agp_disable(rdev);
		}
	}

	r300_mc_init(rdev);

	r = radeon_fence_driver_init(rdev);
	if (r)
		return r;

	r = radeon_bo_init(rdev);
	if (r)
		return r;
	if (rdev->flags & RADEON_IS_PCIE) {
		r = rv370_pcie_gart_init(rdev);
		if (r)
			return r;
	}
	if (rdev->flags & RADEON_IS_PCI) {
		r = r100_pci_gart_init(rdev);
		if (r)
			return r;
	}
	r300_set_reg_safe(rdev);


	radeon_pm_init(rdev);

	rdev->accel_working = true;
	r = r300_startup(rdev);
	if (r) {

		dev_err(rdev->dev, "Disabling GPU acceleration\n");
		r100_cp_fini(rdev);
		radeon_wb_fini(rdev);
		radeon_ib_pool_fini(rdev);
		radeon_irq_kms_fini(rdev);
		if (rdev->flags & RADEON_IS_PCIE)
			rv370_pcie_gart_fini(rdev);
		if (rdev->flags & RADEON_IS_PCI)
			r100_pci_gart_fini(rdev);
		radeon_agp_fini(rdev);
		rdev->accel_working = false;
	}
	return 0;
}
