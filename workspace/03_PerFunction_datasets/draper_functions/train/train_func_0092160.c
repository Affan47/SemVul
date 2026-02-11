append_external_options(char **command, const stp_vars_t *v)
{
  stp_string_list_t *external_options;
  if (! command || ! *command)
    return;
  external_options = stp_get_external_options(v);
  if (external_options)
    {
      int count = stp_string_list_count(external_options);
      int i;
      for (i = 0; i < count; i++)
	{
	  stp_param_string_t *param = stp_string_list_param(external_options, i);
	  char *quoted_name=g_shell_quote(param->name);
	  char *quoted_value=g_shell_quote(param->text);
	  stp_catprintf(command, " -o%s=%s", quoted_name, quoted_value);
	  SAFE_FREE(quoted_name);
	  SAFE_FREE(quoted_value);
	}
      stp_string_list_destroy(external_options);
    }
}
