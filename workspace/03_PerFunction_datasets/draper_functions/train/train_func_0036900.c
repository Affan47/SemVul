acpi_ex_stop_trace_method(struct acpi_namespace_node *method_node,
			  union acpi_operand_object *obj_desc,
			  struct acpi_walk_state *walk_state)
{
	acpi_status status;
	char *pathname = NULL;
	u8 enabled;

	ACPI_FUNCTION_NAME(ex_stop_trace_method);

	if (method_node) {
		pathname = acpi_ns_get_normalized_pathname(method_node, TRUE);
	}

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAILURE(status)) {
		goto exit_path;
	}

	enabled = acpi_ex_interpreter_trace_enabled(NULL);

	(void)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);

	if (enabled) {
		ACPI_TRACE_POINT(ACPI_TRACE_AML_METHOD, FALSE,
				 obj_desc ? obj_desc->method.aml_start : NULL,
				 pathname);
	}

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAILURE(status)) {
		goto exit_path;
	}


	if (acpi_gbl_trace_method_object == obj_desc) {


		if (acpi_gbl_trace_flags & ACPI_TRACE_ONESHOT) {
			acpi_gbl_trace_method_name = NULL;
		}

		acpi_dbg_level = acpi_gbl_original_dbg_level;
		acpi_dbg_layer = acpi_gbl_original_dbg_layer;
		acpi_gbl_trace_method_object = NULL;
	}

	(void)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);

exit_path:
	if (pathname) {
		ACPI_FREE(pathname);
	}
}
