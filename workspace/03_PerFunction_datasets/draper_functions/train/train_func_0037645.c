OCSP_REQ_CTX_add1_header(OCSP_REQ_CTX *rctx,
		const char *name, const char *value)
	{
	if (!name)
		return 0;
	if (BIO_puts(rctx->mem, name) <= 0)
		return 0;
	if (value)
		{
		if (BIO_write(rctx->mem, ": ", 2) != 2)
			return 0;
		if (BIO_puts(rctx->mem, value) <= 0)
			return 0;
		}
	if (BIO_write(rctx->mem, "\r\n", 2) != 2)
		return 0;
	return 1;
	}
