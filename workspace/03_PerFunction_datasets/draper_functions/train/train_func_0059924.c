do_ascii(eap)
    exarg_T	*eap;
{
    int		c;
    char	buf1[20];
    char	buf2[20];
    char_u	buf3[7];
#ifdef FEAT_MBYTE
    int		cc[MAX_MCO];
    int		ci = 0;
    int		len;

    if (enc_utf8)
	c = utfc_ptr2char(ml_get_cursor(), cc);
    else
#endif
	c = gchar_cursor();
    if (c == NUL)
    {
	MSG("NUL");
	return;
    }

#ifdef FEAT_MBYTE
    IObuff[0] = NUL;
    if (!has_mbyte || (enc_dbcs != 0 && c < 0x100) || c < 0x80)
#endif
    {
	if (c == NL)
	    c = NUL;
	if (vim_isprintc_strict(c) && (c < ' '
#ifndef EBCDIC
		    || c > '~'
#endif
			       ))
	{
	    transchar_nonprint(buf3, c);
	    sprintf(buf1, "  <%s>", (char *)buf3);
	}
	else
	    buf1[0] = NUL;
#ifndef EBCDIC
	if (c >= 0x80)
	    sprintf(buf2, "  <M-%s>", transchar(c & 0x7f));
	else
#endif
	    buf2[0] = NUL;
	vim_snprintf((char *)IObuff, IOSIZE,
		_("<%s>%s%s  %d,  Hex %02x,  Octal %03o"),
					   transchar(c), buf1, buf2, c, c, c);
#ifdef FEAT_MBYTE
	if (enc_utf8)
	    c = cc[ci++];
	else
	    c = 0;
#endif
    }

#ifdef FEAT_MBYTE

    while (has_mbyte && (c >= 0x100 || (enc_utf8 && c >= 0x80)))
    {
	len = (int)STRLEN(IObuff);

	if (len > 0)
	    IObuff[len++] = ' ';
	IObuff[len++] = '<';
	if (enc_utf8 && utf_iscomposing(c)
# ifdef USE_GUI
		&& !gui.in_use
# endif
		)
	    IObuff[len++] = ' ';
	len += (*mb_char2bytes)(c, IObuff + len);
	vim_snprintf((char *)IObuff + len, IOSIZE - len,
			c < 0x10000 ? _("> %d, Hex %04x, Octal %o")
				    : _("> %d, Hex %08x, Octal %o"), c, c, c);
	if (ci == MAX_MCO)
	    break;
	if (enc_utf8)
	    c = cc[ci++];
	else
	    c = 0;
    }
#endif

    msg(IObuff);
}
