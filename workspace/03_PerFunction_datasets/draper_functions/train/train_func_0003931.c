bio_new(BIO *bio)
	{
	struct bio_bio_st *b;

	b = OPENSSL_malloc(sizeof *b);
	if (b == NULL)
		return 0;

	b->peer = NULL;
	b->size = 17*1024;
	b->buf = NULL;

	bio->ptr = b;
	return 1;
	}
