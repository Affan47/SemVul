get_expr_register()
{
    char_u	*new_line;

    new_line = getcmdline('=', 0L, 0);
    if (new_line == NULL)
	return NUL;
    if (*new_line == NUL)
	vim_free(new_line);
    else
	set_expr_line(new_line);
    return '=';
}
