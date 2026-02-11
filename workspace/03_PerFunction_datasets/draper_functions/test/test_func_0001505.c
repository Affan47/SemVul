inpar(const filestruct *const foo)
{
    size_t quote_len;

    if (foo == NULL)
	return FALSE;

    quote_len = quote_length(foo->data);

    return (foo->data[quote_len + indent_length(foo->data +
	quote_len)] != '\0');
}
