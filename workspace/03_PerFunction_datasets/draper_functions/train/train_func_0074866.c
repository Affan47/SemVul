update_autos(void)
{
	gchar command[1000];
	GList *unevaluated = NULL, *iter;
	const char *gdb_commands[2];
	int i;


	for (iter = autos; iter; iter = iter->next)
	{
		variable *var = (variable*)iter->data;

		sprintf(command, "-var-delete %s", var->internal->str);
		exec_sync_command(command, TRUE, NULL);
	}

	g_list_foreach(autos, (GFunc)variable_free, NULL);
	g_list_free(autos);
	autos = NULL;


	gdb_commands[0] = g_strdup_printf("-stack-list-arguments 0 %i %i", active_frame, active_frame);
	gdb_commands[1] = "-stack-list-locals 0";
	for (i = 0; i < sizeof (gdb_commands) / sizeof(*gdb_commands); i++)
	{
		gchar *record = NULL, *pos;

		result_class rc = exec_sync_command(gdb_commands[i], TRUE, &record);
		if (RC_DONE != rc)
			break;

		pos = record;
		while ((pos = strstr(pos, "name=\"")))
		{
			variable *var;
			gchar *create_record = NULL, *escaped;

			pos += strlen("name=\"");
			*(strchr(pos, '\"')) = '\0';

			var = variable_new(pos, i ? VT_LOCAL : VT_ARGUMENT);


			escaped = g_strescape(pos, NULL);
			sprintf(command, "-var-create - * \"%s\"", escaped);
			g_free(escaped);


			if (RC_DONE == exec_sync_command(command, TRUE, &create_record))
			{
				gchar *intname = strstr(create_record, "name=\"") + strlen ("name=\"");
				*strchr(intname, '\"') = '\0';
				var->evaluated = TRUE;
				g_string_assign(var->internal, intname);
				autos = g_list_append(autos, var);

				g_free(create_record);
			}
			else
			{
				var->evaluated = FALSE;
				g_string_assign(var->internal, "");
				unevaluated = g_list_append(unevaluated, var);
			}

			pos += strlen(pos) + 1;
		}
		g_free(record);
	}
	g_free((void*)gdb_commands[0]);


	get_variables(autos);


	autos = g_list_concat(autos, unevaluated);
}
