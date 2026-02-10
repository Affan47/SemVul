msg_puts_long_len_attr(longstr, len, attr)
    char_u	*longstr;
    int		len;
    int		attr;
{
    int		slen = len;
    int		room;

    room = Columns - msg_col;
    if (len > room && room >= 20)
    {
	slen = (room - 3) / 2;
	msg_outtrans_len_attr(longstr, slen, attr);
	msg_puts_attr((char_u *)"...", hl_attr(HLF_8));
    }
    msg_outtrans_len_attr(longstr + len - slen, slen, attr);
}
