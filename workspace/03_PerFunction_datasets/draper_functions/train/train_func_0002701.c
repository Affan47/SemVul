gzfile_getc(struct gzfile *gz)
{
    VALUE buf, dst = 0;
    int len;

    len = rb_enc_mbmaxlen(gz->enc);
    while (!ZSTREAM_IS_FINISHED(&gz->z) && gz->z.buf_filled < len) {
	gzfile_read_more(gz);
    }
    if (GZFILE_IS_FINISHED(gz)) {
	if (!(gz->z.flags & GZFILE_FLAG_FOOTER_FINISHED)) {
	    gzfile_check_footer(gz);
	}
	return Qnil;
    }

    if (gz->ec && rb_enc_dummy_p(gz->enc2)) {
	const unsigned char *ss, *sp, *se;
	unsigned char *ds, *dp, *de;
	rb_econv_result_t res;

	if (!gz->cbuf) {
	    gz->cbuf = ALLOC_N(char, GZFILE_CBUF_CAPA);
	}
        ss = sp = (const unsigned char*)RSTRING_PTR(gz->z.buf);
        se = sp + gz->z.buf_filled;
        ds = dp = (unsigned char *)gz->cbuf;
        de = (unsigned char *)ds + GZFILE_CBUF_CAPA;
        res = rb_econv_convert(gz->ec, &sp, se, &dp, de, ECONV_PARTIAL_INPUT|ECONV_AFTER_OUTPUT);
        rb_econv_check_error(gz->ec);
	dst = zstream_shift_buffer(&gz->z, sp - ss);
	gzfile_calc_crc(gz, dst);
	dst = rb_str_new(gz->cbuf, dp - ds);
	rb_enc_associate(dst, gz->enc);
	OBJ_TAINT(dst);
	return dst;
    }
    else {
	buf = gz->z.buf;
	len = rb_enc_mbclen(RSTRING_PTR(buf), RSTRING_END(buf), gz->enc);
	dst = gzfile_read(gz, len);
	return gzfile_newstr(gz, dst);
    }
}
