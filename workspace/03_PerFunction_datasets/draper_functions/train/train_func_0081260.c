e2_command_get_variable_value (gchar *var_name)
{
	gchar *this, *retval;
	gchar *prefix = g_strconcat (var_name, "=", NULL);
	GList *member;
	for (member = variables; member != NULL; member = member->next)
	{
		this = (gchar *)member->data;
		if (g_str_has_prefix (this, prefix))
		{
			retval = this + strlen (prefix);
			return retval;
		}
	}
	return NULL;
}
