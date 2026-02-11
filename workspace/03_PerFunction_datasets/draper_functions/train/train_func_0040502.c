acpi_ut_remove_reference(union acpi_operand_object *object)
{

	ACPI_FUNCTION_NAME(ut_remove_reference);


	if (!object ||
	    (ACPI_GET_DESCRIPTOR_TYPE(object) == ACPI_DESC_TYPE_NAMED)) {
		return;
	}


	if (!acpi_ut_valid_internal_object(object)) {
		return;
	}

	ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
			  "Obj %p Current Refs=%X [To Be Decremented]\n",
			  object, object->common.reference_count));


	(void)acpi_ut_update_object_reference(object, REF_DECREMENT);
	return;
}
