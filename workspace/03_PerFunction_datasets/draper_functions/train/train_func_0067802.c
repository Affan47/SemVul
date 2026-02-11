backspace_until_column(col)
    int	    col;
{
    while ((int)curwin->w_cursor.col > col)
    {
	curwin->w_cursor.col--;
	if (State & REPLACE_FLAG)
	    replace_do_bs();
	else
	    (void)del_char(FALSE);
    }
}
