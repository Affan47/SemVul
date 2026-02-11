char_is_safe(uchar c, bool strict)
{
	return isprint(c) || (!strict && char_is_space(c));
}
