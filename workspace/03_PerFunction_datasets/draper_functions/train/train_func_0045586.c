to_little_endian_double_bytes(UChar *unicode_password, int32_t unicode_password_length)
{
	int32_t i = 0;
	for (i = 0 ; i < unicode_password_length; i++)
	{
		UChar c = unicode_password[i];
		char *byte_ptr = (char*)&(unicode_password[i]);
		byte_ptr[0] = (char)(c & 0xff);
		byte_ptr[1] = (char)(c >> 8);
	}
}
