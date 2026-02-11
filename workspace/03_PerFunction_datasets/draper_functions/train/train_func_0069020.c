re__copy_and_pad(Char *dst, const Char *src, size_t width)
{
	size_t i;

	for (i = 0; i < width; i++) {
		if (*src == '\0')
			break;
		*dst++ = *src++;
	}

	for (; i < width; i++)
		*dst++ = ' ';

	*dst = '\0';
}
