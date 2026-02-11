acpi_ps_update_parameter_list(struct acpi_evaluate_info *info, u16 action)
{
	u32 i;

	if (info->parameters) {


		for (i = 0; info->parameters[i]; i++) {


			(void)acpi_ut_update_object_reference(info->
							      parameters[i],
							      action);
		}
	}
}
