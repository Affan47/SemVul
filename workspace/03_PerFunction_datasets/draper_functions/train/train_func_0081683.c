get_text_data(const gchar *in)
{
	GString	*str;
	gchar	here, next;
	guint	i;

	if((str = g_string_new(NULL)) != NULL)
	{
		if(*in == '"')
			in++;
		for(; (here = *in) != '\0'; in++)
		{
			if(here == '&')
			{
				for(i = 0; i < NUM_ESC_SEQ; i++)
				{
					if(strncmp(in, esc_seq[i].sequence, strlen(esc_seq[i].sequence)) == 0)
					{
						g_string_append_c(str, esc_seq[i].equiv);
						in += strlen(esc_seq[i].sequence) - 1;
						break;
					}
				}
				if(i == NUM_ESC_SEQ)
					xml_error("Unknown &-sequence ignored");
			}
			else if(here == '\\')
			{
				if((next = *(in + 1)) == '\0')
					break;
				switch(next)
				{
					case '\\':
						g_string_append_c(str, '\\');
						break;
					case '"':
						g_string_append_c(str, '"');
						break;
					default:
						xml_error("Unsupported backslash escaped character '%c'!", next);
				}
				in++;
			}
			else if(!(here == '"' && *(in + 1) == '\0'))
				g_string_append_c(str, here);
		}
	}
	return str;
}
