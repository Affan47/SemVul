acpi_db_display_argument_object(union acpi_operand_object *obj_desc,
				struct acpi_walk_state *walk_state)
{

	if (!acpi_gbl_cm_single_step) {
		return;
	}

	acpi_os_printf("ArgObj:  ");
	acpi_db_display_internal_object(obj_desc, walk_state);
}
