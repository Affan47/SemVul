bgx_acpi_match_id(acpi_handle handle, u32 lvl,
				     void *context, void **ret_val)
{
	struct acpi_buffer string = { ACPI_ALLOCATE_BUFFER, NULL };
	struct bgx *bgx = context;
	char bgx_sel[5];

	snprintf(bgx_sel, 5, "BGX%d", bgx->bgx_id);
	if (ACPI_FAILURE(acpi_get_name(handle, ACPI_SINGLE_NAME, &string))) {
		pr_warn("Invalid link device\n");
		return AE_OK;
	}

	if (strncmp(string.pointer, bgx_sel, 4))
		return AE_OK;

	acpi_walk_namespace(ACPI_TYPE_DEVICE, handle, 1,
			    bgx_acpi_register_phy, NULL, bgx, NULL);

	kfree(string.pointer);
	return AE_CTRL_TERMINATE;
}
