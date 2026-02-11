unichars_to_big5(const unichar *str, char *out)
{
	for (; *str != '\0'; str++) {
		if (*str > 0xff)
			*out++ = (*str >> 8) & 0xff;
		*out++ = *str & 0xff;
	}
	*out = '\0';
}
