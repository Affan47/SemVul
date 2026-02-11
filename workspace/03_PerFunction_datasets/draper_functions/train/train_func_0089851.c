get_symbol_length(char *symbol)
{
	struct gnu_request *req;
	int len;

	req = (struct gnu_request *)GETBUF(sizeof(struct gnu_request));
	if (get_symbol_type(symbol, NULL, req) == TYPE_CODE_UNDEF)
		error(FATAL, "cannot determine length of symbol: %s\n",
			symbol);

	len = (int)req->length;
	FREEBUF(req);

	return len;
}
