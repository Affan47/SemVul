concat_list(struct string_list *start, ...)
{
	va_list ap;
	struct string_list *n, *n2;

	if (!start)
		return NULL;
	for (va_start(ap, start); (n = va_arg(ap, struct string_list *));) {
		for (n2 = n; n2->next; n2 = n2->next)
			;
		n2->next = start;
		start = n;
	}
	va_end(ap);
	return start;
}
