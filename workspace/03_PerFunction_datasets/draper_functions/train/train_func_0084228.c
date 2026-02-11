chartabsize(c, col)
	register int	c;
	long			col;
{
#ifdef KANJI
	if (c >= ' ' &&  c != DEL)
	{
		if (c < 0x80 || ISdisp(c))
			return(1);
		return(4);
	}
#else
	if ((c >= ' ' && (c <= '~' || p_gr)) || c > 0xa0)
   		return 1;
#endif
   	else if (c == TAB && !curwin->w_p_list)
   		return (int)(curbuf->b_p_ts - (col % curbuf->b_p_ts));
   	else
		return 2;
}
