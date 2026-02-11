close_context(context_def)
	char	*context_def;
{
	char		*src, *help_ptr;
	struct context	*context_ptr;

	src=context_def;
	while ( (all_contexts != NULL) && ((help_ptr=get_word(&src)) != NULL) ) {
		if ( (context_ptr=find_context(help_ptr)) != NULL )
			unlink_context(context_ptr);
		(void) free(help_ptr);
	}
	return;
}
