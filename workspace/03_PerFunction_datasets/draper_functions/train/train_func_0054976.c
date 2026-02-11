gfire_sq_ase_strip_color_codes(const gchar *p_str)
{
	GString *str = g_string_new(NULL);

	while(*p_str)
	{
		const gchar *next = strchr(p_str + 1, '$');
		if(!next)
			next = strchr(p_str + 1, 0);

		if(*p_str == '$')
		{
			int i = 0;
			while(aseCodes[i].ch)
			{
				if(*(p_str + 1) == aseCodes[i].ch)
				{
					g_string_append_len(str, p_str + 2, next - p_str - 2);
					break;
				}
				i++;
			}

			if(!aseCodes[i].ch)
				g_string_append_len(str, p_str, next - p_str);
		}
		else
			g_string_append_len(str, p_str, next - p_str);

		p_str = next;
	}

	return g_string_free(str, FALSE);
}
