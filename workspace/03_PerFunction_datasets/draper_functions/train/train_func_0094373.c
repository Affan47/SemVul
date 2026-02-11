unparse_arglist(Stream * str, Arg_List * args)
{
    while (args) {
	if (args->kind == ARG_SPLICE)
	    stream_add_char(str, '@');
	unparse_expr(str, args->expr);
	if (args->next)
	    stream_add_string(str, ", ");
	args = args->next;
    }
}
