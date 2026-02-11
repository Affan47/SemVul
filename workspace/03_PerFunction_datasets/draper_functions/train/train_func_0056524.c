acpi_get_handle(acpi_handle parent,
		acpi_string pathname, acpi_handle * ret_handle)
{
	acpi_status status;
	struct acpi_namespace_node *node = NULL;
	struct acpi_namespace_node *prefix_node = NULL;

	ACPI_FUNCTION_ENTRY();


	if (!ret_handle || !pathname) {
		return (AE_BAD_PARAMETER);
	}


	if (parent) {
		prefix_node = acpi_ns_validate_handle(parent);
		if (!prefix_node) {
			return (AE_BAD_PARAMETER);
		}
	}


	if (ACPI_IS_ROOT_PREFIX(pathname[0])) {


		if (!strcmp(pathname, ACPI_NS_ROOT_PATH)) {
			*ret_handle =
			    ACPI_CAST_PTR(acpi_handle, acpi_gbl_root_node);
			return (AE_OK);
		}
	} else if (!prefix_node) {


		return (AE_BAD_PARAMETER);
	}


	status =
	    acpi_ns_get_node(prefix_node, pathname, ACPI_NS_NO_UPSEARCH, &node);
	if (ACPI_SUCCESS(status)) {
		*ret_handle = ACPI_CAST_PTR(acpi_handle, node);
	}

	return (status);
}
