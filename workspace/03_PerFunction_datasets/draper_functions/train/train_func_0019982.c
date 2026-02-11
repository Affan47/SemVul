parse_rle_data_truecolor(TGAContext *ctx)
{
	TGAColor col;
	guint rle_num, raw_num;
	guchar *s, tag;
	guint n = 0;

	g_return_val_if_fail(ctx->in->size > 0, 0);
	s = ctx->in->data;

	for (n = 0; n < ctx->in->size; ) {
		tag = *s;
		s++, n++;
		if (tag & 0x80) {
			if (n + ctx->pbuf->n_channels >= ctx->in->size) {
				return --n;
			} else {
				rle_num = (tag & 0x7f) + 1;
				col.b = *s++;
				col.g = *s++;
				col.r = *s++;
				if (ctx->hdr->bpp == 32)
					col.a = *s++;
				n += ctx->pbuf->n_channels;
				write_rle_data(ctx, &col, &rle_num);
				if (ctx->pbuf_bytes_done == ctx->pbuf_bytes) {
					ctx->done = TRUE;
					return n;
				}
			}
		} else {
			raw_num = tag + 1;
			if (n + (raw_num * ctx->pbuf->n_channels) >= ctx->in->size) {
				return --n;
			} else {
				for (; raw_num; raw_num--) {
					ctx->pptr[2] = *s++;
					ctx->pptr[1] = *s++;
					ctx->pptr[0] = *s++;
					if (ctx->hdr->bpp == 32)
						ctx->pptr[3] = *s++;
					n += ctx->pbuf->n_channels;
					ctx->pptr += ctx->pbuf->n_channels;
					ctx->pbuf_bytes_done += ctx->pbuf->n_channels;
					if (ctx->pbuf_bytes_done == ctx->pbuf_bytes) {
						ctx->done = TRUE;
						return n;
					}
				}

				if (ctx->pbuf_bytes_done == ctx->pbuf_bytes) {
					ctx->done = TRUE;
					return n;
				}
			}
		}
	}
	if (ctx->pbuf_bytes_done == ctx->pbuf_bytes)
		ctx->done = TRUE;
	return n;
}
