xwcslcpy(CHAR_T *dst, const CHAR_T *src, size_t size) {

	register size_t i, n = size;

	for (i = 0; n > 1 && src[i]; i++, n--)
		dst[i] = src[i];

	if (n)
		dst[i] = 0;

	while (src[i])
		i++;

	return i;
}
