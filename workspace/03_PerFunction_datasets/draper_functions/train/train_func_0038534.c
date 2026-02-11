sha1flush(struct sha1file *f)
{
	unsigned offset = f->offset;

	if (offset) {
		SHA1_Update(&f->ctx, f->buffer, offset);
		flush(f, offset);
		f->offset = 0;
	}
}
