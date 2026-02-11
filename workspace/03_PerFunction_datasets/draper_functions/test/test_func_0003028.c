col_print(buf, col, vcol)
    char_u  *buf;
    int	    col;
    int	    vcol;
{
    if (col == vcol)
	sprintf((char *)buf, "%d", col);
    else
	sprintf((char *)buf, "%d-%d", col, vcol);
}
