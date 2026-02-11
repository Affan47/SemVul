_iconv_close(iconv_t * cd)
{
	static const iconv_t invalid = (iconv_t) -1;

	if (*cd != invalid) {
		tds_sys_iconv_close(*cd);
		*cd = invalid;
	}
}
