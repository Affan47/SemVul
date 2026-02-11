in_html_tag(end_tag)
    int		end_tag;
{
    char_u	*line = ml_get_curline();
    char_u	*p;
    int		c;
    int		lc = NUL;
    pos_T	pos;

#ifdef FEAT_MBYTE
    if (enc_dbcs)
    {
	char_u	*lp = NULL;


	for (p = line; p < line + curwin->w_cursor.col; mb_ptr_adv(p))
	    if (*p == '>' || *p == '<')
	    {
		lc = *p;
		lp = p;
	    }
	if (*p != '<')
	{
	    if (lc != '<')
		return FALSE;
	    p = lp;
	}
    }
    else
#endif
    {
	for (p = line + curwin->w_cursor.col; p > line; )
	{
	    if (*p == '<')
		break;
	    mb_ptr_back(line, p);
	    if (*p == '>')
		break;
	}
	if (*p != '<')
	    return FALSE;
    }

    pos.lnum = curwin->w_cursor.lnum;
    pos.col = (colnr_T)(p - line);

    mb_ptr_adv(p);
    if (end_tag)

	return *p == '/';


    if (*p == '/')
	return FALSE;


    for (;;)
    {
	if (inc(&pos) < 0)
	    return FALSE;
	c = *ml_get_pos(&pos);
	if (c == '>')
	    break;
	lc = c;
    }
    return lc != '/';
}
