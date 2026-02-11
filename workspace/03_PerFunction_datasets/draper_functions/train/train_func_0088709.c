spell_word_start(startcol)
    int		startcol;
{
    char_u	*line;
    char_u	*p;
    int		col = 0;

    if (no_spell_checking(curwin))
	return startcol;


    line = ml_get_curline();
    for (p = line + startcol; p > line; )
    {
	mb_ptr_back(line, p);
	if (spell_iswordp_nmw(p))
	    break;
    }


    while (p > line)
    {
	col = (int)(p - line);
	mb_ptr_back(line, p);
	if (!spell_iswordp(p, curwin))
	    break;
	col = 0;
    }

    return col;
}
