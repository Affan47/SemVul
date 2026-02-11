trace_create_failure( char *new_name, char *old_name, u16 fc_tokn)
{
    bool not_alias   = BOOLVAL( old_name == NULL );
    bool do_it       = is_on_trace_list( new_name);

    if ( ( ! do_it ) && ( ! not_alias ) )
    {
        do_it       = is_on_trace_list( old_name);
    }

    if ( do_it )
    {
	char  fc_token_display[TRACING_FCODE_LENGTH] = "";
	char *as_alias   = not_alias ? "" : " as an ALIAS to ";
	char *alias_name = not_alias ? "" : old_name;

	if ( fc_tokn > 0 )
	{
	   tracing_fcode( fc_token_display, fc_tokn);
	}
	tokenization_error(TRACER,
		"Failed to create %s"
		"%s"
		"%s"
		"%s\n",
		new_name, fc_token_display,
		    as_alias, alias_name);
    }
}
