textToBlob(text *t, blob *b, int destroy)
{
	size_t s;
	blob *bin;

	if(t == NULL)
		return NULL;

	s = 0;

	(void)textIterate(t, getLength, &s, 0);

	if(s == 0)
		return b;


	bin = b;
	if(b == NULL) {
		b = blobCreate();

		if(b == NULL)
			return NULL;
	}

	if(blobGrow(b, s) != CL_SUCCESS) {
		cli_warnmsg("Couldn't grow the blob: we may be low on memory\n");
#if	0
		if(!destroy) {
			if(bin == NULL)
				blobDestroy(b);
			return NULL;
		}


#else
		if(bin == NULL)
			blobDestroy(b);
		return NULL;
#endif
	}

	(void)textIterate(t, addToBlob, b, destroy);

	if(destroy && t->t_next) {
		textDestroy(t->t_next);
		t->t_next = NULL;
	}

	blobClose(b);

	return b;
}
