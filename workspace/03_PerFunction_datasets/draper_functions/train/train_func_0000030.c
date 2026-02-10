foldAddMarker(lnum, marker, markerlen)
    linenr_T	lnum;
    char_u	*marker;
    int		markerlen;
{
    char_u	*cms = curbuf->b_p_cms;
    char_u	*line;
    int		line_len;
    char_u	*newline;
    char_u	*p = (char_u *)strstr((char *)curbuf->b_p_cms, "%s");


    line = ml_get(lnum);
    line_len = (int)STRLEN(line);

    if (u_save(lnum - 1, lnum + 1) == OK)
    {
	newline = alloc((unsigned)(line_len + markerlen + STRLEN(cms) + 1));
	if (newline == NULL)
	    return;
	STRCPY(newline, line);
	if (p == NULL)
	    vim_strncpy(newline + line_len, marker, markerlen);
	else
	{
	    STRCPY(newline + line_len, cms);
	    STRNCPY(newline + line_len + (p - cms), marker, markerlen);
	    STRCPY(newline + line_len + (p - cms) + markerlen, p + 2);
	}

	ml_replace(lnum, newline, FALSE);
    }
}
