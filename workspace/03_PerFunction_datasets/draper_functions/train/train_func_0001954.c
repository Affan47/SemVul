pdf_parse_bf_range_array(fz_context *ctx, pdf_cmap *cmap, fz_stream *file, pdf_lexbuf *buf, int lo, int hi)
{
	int tok;
	int dst[256];
	int i;

	while (1)
	{
		tok = pdf_lex_cmap(file, buf);

		if (tok == PDF_TOK_CLOSE_ARRAY)
			return;


		else if (tok != PDF_TOK_STRING)
			fz_throw(ctx, "expected string or ]");

		if (buf->len / 2)
		{
			for (i = 0; i < buf->len / 2; i++)
				dst[i] = pdf_code_from_string(&buf->scratch[i * 2], 2);

			pdf_map_one_to_many(ctx, cmap, lo, dst, buf->len / 2);
		}

		lo ++;
	}
}
