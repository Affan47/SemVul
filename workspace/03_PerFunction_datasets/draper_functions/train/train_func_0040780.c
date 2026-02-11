unichar_is_control(U32 c)
{
	return (c >= 0x80) ? c <= 0xa0 : (asciichar_attr[c] & CHARATTR_CONTROL);
}
