acpi_ut_method_error(const char *module_name,
		     u32 line_number,
		     const char *message,
		     struct acpi_namespace_node *prefix_node,
		     const char *path, acpi_status method_status)
{
	acpi_status status;
	struct acpi_namespace_node *node = prefix_node;

	ACPI_MSG_REDIRECT_BEGIN;
	acpi_os_printf(ACPI_MSG_ERROR);

	if (path) {
		status =
		    acpi_ns_get_node(prefix_node, path, ACPI_NS_NO_UPSEARCH,
				     &node);
		if (ACPI_FAILURE(status)) {
			acpi_os_printf("[Could not get node by pathname]");
		}
	}

	acpi_ns_print_node_pathname(node, message);
	acpi_os_printf(", %s", acpi_format_exception(method_status));

	ACPI_MSG_SUFFIX;
	ACPI_MSG_REDIRECT_END;
}
