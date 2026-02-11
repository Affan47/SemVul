UT_UCS4_strlen_as_char(const UT_UCS4Char * string)
{
	UT_uint32 i = 0;

	char d[4];

	UT_Wctomb w(XAP_EncodingManager::get_instance()->getNative8BitEncodingName());

	while (*string != 0)
	  {
		int length;
		w.wctomb_or_fallback(d,length,*string++);
		i+=length;
	  }

	return i;
}
