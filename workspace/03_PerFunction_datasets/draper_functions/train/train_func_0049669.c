my_bio_read (BIO *b, char *buf, int len)
{
	struct ikstls_data *data = (struct ikstls_data *) b->ptr;
	int ret;

	if (buf == NULL || len <= 0 || data == NULL) return 0;

	ret = data->trans->recv (data->sock, buf, len, data->timeout);
	BIO_clear_retry_flags (b);
	return ret;
}
