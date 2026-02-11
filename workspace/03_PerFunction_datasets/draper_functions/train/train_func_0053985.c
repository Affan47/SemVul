ci_dpm_setup_asic(struct radeon_device *rdev)
{
	int r;

	r = ci_mc_load_microcode(rdev);
	if (r)
		DRM_ERROR("Failed to load MC firmware!\n");
	ci_read_clock_registers(rdev);
	ci_get_memory_type(rdev);
	ci_enable_acpi_power_management(rdev);
	ci_init_sclk_t(rdev);
}
