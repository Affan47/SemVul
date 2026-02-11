pdf_from_ucs2(pdf_document *xref, unsigned short *src)
{
	fz_context *ctx = xref->ctx;
	int i, j, len;
	char *docstr;

	len = 0;
	while (src[len])
		len++;

	docstr = fz_malloc(ctx, len + 1);

	for (i = 0; i < len; i++)
	{

		if (0 < src[i] && src[i] < 256 && pdf_doc_encoding[src[i]] == src[i]) {
			docstr[i] = src[i];
			continue;
		}


		for (j = 0; j < 256; j++)
			if (pdf_doc_encoding[j] == src[i])
				break;
		docstr[i] = j;


		if (!docstr[i])
		{
			fz_free(ctx, docstr);
			return NULL;
		}
	}
	docstr[len] = '\0';

	return docstr;
}
