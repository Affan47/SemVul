applix_read_sheet_table (ApplixReadState *state)
{
	unsigned char *ptr;
	unsigned char *std_name, *real_name;
	while (NULL != (ptr = applix_get_line (state))) {
	       if (!a_strncmp (ptr, "END SHEETS TABLE"))
		       return FALSE;


	       std_name = ptr + 6;
	       ptr = strchr (std_name, ':');
	       if (ptr == NULL)
		       continue;
	       *ptr = '\0';

	       real_name = ptr + 3;
	       ptr = strchr (real_name, '~');
	       if (ptr == NULL)
		       continue;
	       *ptr = '\0';

	       state->std_names  = g_slist_prepend (state->std_names,
						    g_strdup (std_name));
	       state->real_names = g_slist_prepend (state->real_names,
						    g_strdup (real_name));
	}
	return TRUE;
}
