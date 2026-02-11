fixthisline(get_the_indent)
    int (*get_the_indent) __ARGS((void));
{
    change_indent(INDENT_SET, get_the_indent(), FALSE, 0, TRUE);
    if (linewhite(curwin->w_cursor.lnum))
	did_ai = TRUE;
}
