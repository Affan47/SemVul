acpi_ut_exit(u32 line_number,
	     const char *function_name,
	     const char *module_name, u32 component_id)
{


	if (ACPI_IS_DEBUG_ENABLED(ACPI_LV_FUNCTIONS, component_id)) {
		acpi_debug_print(ACPI_LV_FUNCTIONS,
				 line_number, function_name, module_name,
				 component_id, "%s\n", acpi_gbl_fn_exit_str);
	}

	if (acpi_gbl_nesting_level) {
		acpi_gbl_nesting_level--;
	}
}
