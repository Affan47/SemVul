bgx_init_phy(struct bgx *bgx)
{
	if (!acpi_disabled)
		return bgx_init_acpi_phy(bgx);

	return bgx_init_of_phy(bgx);
}
