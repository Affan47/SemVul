del_char_after_col(limit_col)
    int limit_col UNUSED;
{
#ifdef FEAT_MBYTE
    if (enc_utf8 && limit_col >= 0)
    {
	colnr_T ecol = curwin->w_cursor.col + 1;


	mb_adjust_cursor();
	while (curwin->w_cursor.col < (colnr_T)limit_col)
	{
	    int l = utf_ptr2len(ml_get_cursor());

	    if (l == 0)
		break;
	    curwin->w_cursor.col += l;
	}
	if (*ml_get_cursor() == NUL || curwin->w_cursor.col == ecol)
	    return FALSE;
	del_bytes((long)((int)ecol - curwin->w_cursor.col), FALSE, TRUE);
    }
    else
#endif
	(void)del_char(FALSE);
    return TRUE;
}
