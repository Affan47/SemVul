fmt_H(int pack, int len, blob_t *b, va_list *ap)
{
	if (len) return (-1);

	if (pack) {
		uint16_t n = va_arg(*ap, int);
		n = htons(n);
		if (blob_write(b, &n, sizeof(n)) < 0)
			return (-1);
	} else {
		uint16_t *n = va_arg(*ap, uint16_t *);
		if (blob_read(b, n, sizeof(*n)) != sizeof(*n))
			return (-1);
		*n = ntohs(*n);
	}
	return (0);
}
