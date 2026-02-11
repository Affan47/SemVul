rv770_enable_acpi_pm(struct radeon_device *rdev)
{
	WREG32_P(GENERAL_PWRMGT, STATIC_PM_EN, ~STATIC_PM_EN);
}
