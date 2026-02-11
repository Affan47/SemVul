md5_final(MD5Context *ctx, guchar digest[16])
{
	guint32 count;
	guchar *p;


	count = (ctx->bits[0] >> 3) & 0x3F;


	p = ctx->in + count;
	*p++ = 0x80;


	count = 64 - 1 - count;


	if (count < 8) {

		memset(p, 0, count);
		if (ctx->doByteReverse)
			_byte_reverse(ctx->in, 16);
		md5_transform(ctx->buf, (guint32 *) ctx->in);


		memset(ctx->in, 0, 56);
	} else {

		memset(p, 0, count - 8);
	}
	if (ctx->doByteReverse)
		_byte_reverse(ctx->in, 14);


	((guint32 *) ctx->in)[14] = ctx->bits[0];
	((guint32 *) ctx->in)[15] = ctx->bits[1];

	md5_transform(ctx->buf, (guint32 *) ctx->in);
	if (ctx->doByteReverse)
		_byte_reverse((guchar *) ctx->buf, 4);
	memcpy(digest, ctx->buf, 16);
}
