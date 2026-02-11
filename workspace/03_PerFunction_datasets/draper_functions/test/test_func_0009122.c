vim_iswordc_buf(c, buf)
    int		c;
    buf_T	*buf;
{
#ifdef FEAT_MBYTE
    if (c >= 0x100)
    {
	if (enc_dbcs != 0)
	    return dbcs_class((unsigned)c >> 8, (unsigned)(c & 0xff)) >= 2;
	if (enc_utf8)
	    return utf_class(c) >= 2;
    }
#endif
    return (c > 0 && c < 0x100 && GET_CHARTAB(buf, c) != 0);
}
