acpi_ds_clear_implicit_return(struct acpi_walk_state *walk_state)
{
	ACPI_FUNCTION_NAME(ds_clear_implicit_return);


	if (!acpi_gbl_enable_interpreter_slack) {
		return;
	}

	if (walk_state->implicit_return_obj) {


		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
				  "Removing reference on stale implicit return obj %p\n",
				  walk_state->implicit_return_obj));

		acpi_ut_remove_reference(walk_state->implicit_return_obj);
		walk_state->implicit_return_obj = NULL;
	}
}
