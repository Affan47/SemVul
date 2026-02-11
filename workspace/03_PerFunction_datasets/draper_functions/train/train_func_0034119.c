acpi_set(gboolean on)
{
	FILE *fp = NULL;

	if (!acpiprefs.file_path) {
		debug_print("acpiprefs.file_path NULL\n");
		return;
	}
	if (!check_impl(acpiprefs.file_path)) {
		debug_print("acpiprefs.file_path not implemented\n");
		return;
	}
	if (!acpiprefs.on_param || !acpiprefs.off_param) {
		debug_print("no param\n");
		return;
	}

	if (!is_program(acpiprefs.file_path)) {
		fp = fopen(acpiprefs.file_path, "wb");
		if (fp == NULL)
			return;

		if (on) {
			fwrite(acpiprefs.on_param, 1, strlen(acpiprefs.on_param), fp);
		} else {
			fwrite(acpiprefs.off_param, 1, strlen(acpiprefs.off_param), fp);
		}
		fclose(fp);
	} else {
		gchar *cmd = g_strdup_printf("%s %s",
				acpiprefs.file_path,
				on ? acpiprefs.on_param:acpiprefs.off_param);
		execute_command_line(cmd, TRUE);
		g_free(cmd);
	}
}
