_e2_command_handle_variable_value (gchar *var_name, gchar *value)
{
	gchar *this;
	GList *member;
	g_strstrip (var_name);
	g_strstrip (value);
	if (*var_name == '\0')
	{
		if (*value == '\0')
		{
			for (member = variables; member != NULL; member = member->next)
				e2_output_print (&app.tab, (gchar *)member->data, NULL, FALSE, NULL);
			e2_output_print_end (&app.tab, FALSE);
		}
		else
		{
			this = g_strconcat ("=", value, NULL);
			for (member = variables; member != NULL; member = member->next)
			{
				if (g_str_has_suffix ((gchar*)member->data, this))
				{
					e2_output_print (&app.tab, (gchar *)member->data, NULL, FALSE, NULL);
					break;
				}
			}
			g_free (this);
		}
	}
	else
	{
		gchar *prefix = g_strconcat (var_name, "=", NULL);
		for (member = variables; member != NULL; member = member->next)
		{
			this = (gchar *)member->data;
			if (g_str_has_prefix (this, prefix))
			{
				g_free (this);
				if (*value == '\0')
					variables = g_list_delete_link (variables, member);
				else
					member->data = g_strconcat (prefix, value, NULL);
				return;
			}
		}
		this = g_strconcat (prefix, value, NULL);
		variables = g_list_append (variables, this);
	}
}
