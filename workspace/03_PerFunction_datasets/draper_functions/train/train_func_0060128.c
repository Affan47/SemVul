acpi_ds_method_data_delete_all(struct acpi_walk_state *walk_state)
{
	u32 index;

	ACPI_FUNCTION_TRACE(ds_method_data_delete_all);


	for (index = 0; index < ACPI_METHOD_NUM_LOCALS; index++) {
		if (walk_state->local_variables[index].object) {
			ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Deleting Local%u=%p\n",
					  index,
					  walk_state->local_variables[index].
					  object));


			acpi_ns_detach_object(&walk_state->
					      local_variables[index]);
		}
	}


	for (index = 0; index < ACPI_METHOD_NUM_ARGS; index++) {
		if (walk_state->arguments[index].object) {
			ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Deleting Arg%u=%p\n",
					  index,
					  walk_state->arguments[index].object));


			acpi_ns_detach_object(&walk_state->arguments[index]);
		}
	}

	return_VOID;
}
