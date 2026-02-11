cinclude(void)
{
	char *c;
	if ((c = strchr(yytext, '<')) == NULL)
		*strchr(c = strchr(yytext, '"') + 1, '"') = 0;
	else
		*strchr(++c, '>') = 0;


	if (include_stack_ptr >= MAX_INCLUDE_DEPTH)
	{
		conf_report_error("Includes nested too deep (max is %d)", MAX_INCLUDE_DEPTH);
	}
	else
	{
		FILE *tmp_fbfile_in;

		tmp_fbfile_in = fopen(c, "r");

		if (tmp_fbfile_in == NULL)
		{

			char fnamebuf[IRCD_BUFSIZE];

			rb_snprintf(fnamebuf, sizeof(fnamebuf), "%s/%s", ETCPATH, c);
			tmp_fbfile_in = fopen(fnamebuf, "r");


			if(tmp_fbfile_in == NULL)
			{
				conf_report_error("Include %s: %s.", c, strerror(errno));
				return;
			}
		}
		lineno_stack[include_stack_ptr] = lineno;
		lineno = 1;
		inc_fbfile_in[include_stack_ptr] = conf_fbfile_in;
		strcpy(conffile_stack[include_stack_ptr], c);
		current_file = conffile_stack[include_stack_ptr];
		include_stack[include_stack_ptr++] = YY_CURRENT_BUFFER;
		conf_fbfile_in = tmp_fbfile_in;
		yy_switch_to_buffer(yy_create_buffer(yyin,YY_BUF_SIZE));
	}
}
