load_module(char *name, int len)
{
    mstack.buffer[mstack.index++] = YY_CURRENT_BUFFER;
    if (mstack.index == MAX_DEPTH)
	fatal_error(_("Too many levels of inclusion"));
    yyin = fopen(name, "r");
    if (yyin == NULL) fatal_error(_("Unable to open module"));
    yy_switch_to_buffer(yy_create_buffer(yyin,YY_BUF_SIZE));
    start_buffer();
    add_string(name, len);
    mstack.name[mstack.index] = get_buffer();
    mstack.lineno[mstack.index] = 1;
}
