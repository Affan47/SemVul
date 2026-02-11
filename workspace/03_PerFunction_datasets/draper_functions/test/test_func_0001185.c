trunc_string(s, buf, room)
    char_u	*s;
    char_u	*buf;
    int		room;
{
    int		half;
    int		len;
    int		e;
    int		i;
    int		n;

    room -= 3;
    half = room / 2;
    len = 0;


    for (e = 0; len < half; ++e)
    {
	if (s[e] == NUL)
	{

	    buf[e] = NUL;
	    return;
	}
	n = ptr2cells(s + e);
	if (len + n >= half)
	    break;
	len += n;
	buf[e] = s[e];
#ifdef FEAT_MBYTE
	if (has_mbyte)
	    for (n = (*mb_ptr2len)(s + e); --n > 0; )
	    {
		++e;
		buf[e] = s[e];
	    }
#endif
    }


    i = e;
#ifdef FEAT_MBYTE
    if (enc_dbcs != 0)
    {


	n = vim_strsize(s + i);
	while (len + n > room)
	{
	    n -= ptr2cells(s + i);
	    i += (*mb_ptr2len)(s + i);
	}
    }
    else if (enc_utf8)
    {

	half = i = (int)STRLEN(s);
	for (;;)
	{
	    do
		half = half - (*mb_head_off)(s, s + half - 1) - 1;
	    while (utf_iscomposing(utf_ptr2char(s + half)) && half > 0);
	    n = ptr2cells(s + half);
	    if (len + n > room)
		break;
	    len += n;
	    i = half;
	}
    }
    else
#endif
    {
	for (i = (int)STRLEN(s); len + (n = ptr2cells(s + i - 1)) <= room; --i)
	    len += n;
    }


    mch_memmove(buf + e, "...", (size_t)3);
    STRMOVE(buf + e + 3, s + i);
}
