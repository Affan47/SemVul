acpi_db_display_objects(char *obj_type_arg, char *display_count_arg)
{
	struct acpi_walk_info info;
	acpi_object_type type;
	struct acpi_object_info *object_info;
	u32 i;
	u32 total_objects = 0;


	if (!obj_type_arg) {
		object_info =
		    ACPI_ALLOCATE_ZEROED(sizeof(struct acpi_object_info));


		(void)acpi_walk_namespace(ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
					  ACPI_UINT32_MAX,
					  acpi_db_walk_for_object_counts, NULL,
					  (void *)object_info, NULL);

		acpi_os_printf("\nSummary of namespace objects:\n\n");

		for (i = 0; i < ACPI_TOTAL_TYPES; i++) {
			acpi_os_printf("%8u %s\n", object_info->types[i],
				       acpi_ut_get_type_name(i));

			total_objects += object_info->types[i];
		}

		acpi_os_printf("\n%8u Total namespace objects\n\n",
			       total_objects);

		ACPI_FREE(object_info);
		return (AE_OK);
	}


	type = acpi_db_match_argument(obj_type_arg, acpi_db_object_types);
	if (type == ACPI_TYPE_NOT_FOUND) {
		acpi_os_printf("Invalid or unsupported argument\n");
		return (AE_OK);
	}

	acpi_db_set_output_destination(ACPI_DB_DUPLICATE_OUTPUT);
	acpi_os_printf
	    ("Objects of type [%s] defined in the current ACPI Namespace:\n",
	     acpi_ut_get_type_name(type));

	acpi_db_set_output_destination(ACPI_DB_REDIRECTABLE_OUTPUT);

	info.count = 0;
	info.owner_id = ACPI_OWNER_ID_MAX;
	info.debug_level = ACPI_UINT32_MAX;
	info.display_type = ACPI_DISPLAY_SUMMARY | ACPI_DISPLAY_SHORT;


	(void)acpi_walk_namespace(type, ACPI_ROOT_OBJECT, ACPI_UINT32_MAX,
				  acpi_db_walk_for_specific_objects, NULL,
				  (void *)&info, NULL);

	acpi_os_printf
	    ("\nFound %u objects of type [%s] in the current ACPI Namespace\n",
	     info.count, acpi_ut_get_type_name(type));

	acpi_db_set_output_destination(ACPI_DB_CONSOLE_OUTPUT);
	return (AE_OK);
}
