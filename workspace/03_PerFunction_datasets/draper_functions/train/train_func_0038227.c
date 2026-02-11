UT_UCS4_strcpy_char(UT_UCS4Char * dest, const char * src)
{
	UT_ASSERT(dest);
	UT_ASSERT(src);

	UT_UCS4Char * d 		= dest;
	const char * s	= static_cast<const char *>(src);

	static UT_UCS4_mbtowc m(XAP_EncodingManager::get_instance()->getNative8BitEncodingName());
	UT_UCS4Char wc;

	while (*s != 0)
	  {
		if(m.mbtowc(wc,*s))*d++=wc;
		s++;
	  }
	*d = 0;

	return dest;
}
