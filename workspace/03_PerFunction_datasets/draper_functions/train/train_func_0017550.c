acpi_atlas_button_setup(acpi_handle region_handle,
		    u32 function, void *handler_context, void **return_context)
{
	*return_context =
		(function != ACPI_REGION_DEACTIVATE) ? handler_context : NULL;

	return AE_OK;
}
