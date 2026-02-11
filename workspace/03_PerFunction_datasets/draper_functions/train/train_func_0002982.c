escape (char *dest, char *src, size_t len)
{
	char c;
	int i;
	int j = 0;

	for (i = 0; i < len; i++) {
		c = src[i];
		if ('&' == c || '<' == c || '>' == c || '\'' == c || '"' == c) {
			if (i - j > 0) dest = my_strcat (dest, src + j, i - j);
			j = i + 1;
			switch (c) {
			case '&': dest = my_strcat (dest, "&amp;", 5); break;
			case '\'': dest = my_strcat (dest, "&apos;", 6); break;
			case '"': dest = my_strcat (dest, "&quot;", 6); break;
			case '<': dest = my_strcat (dest, "&lt;", 4); break;
			case '>': dest = my_strcat (dest, "&gt;", 4); break;
			}
		}
	}
	if (i - j > 0) dest = my_strcat (dest, src + j, i - j);
	return dest;
}
