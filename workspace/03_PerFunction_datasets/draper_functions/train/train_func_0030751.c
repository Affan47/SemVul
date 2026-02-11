buffer_mod_getnc(char *ptr, long n, void *f)
{
	BUFFERED_MOD *bm = f;
	if (bm->buffered) {
		int left = bm->len - bm->ptr;
		if (n >= left) {
			int rv;
			memcpy(ptr, bm->buffered + bm->ptr, left);
			free(bm->buffered);
			bm->buffered = NULL;
			rv = dumbfile_getnc(ptr + left, n - left, bm->remaining);
			return left + MAX(rv, 0);
		}
		memcpy(ptr, bm->buffered + bm->ptr, n);
		bm->ptr += n;
		return n;
	}
	return dumbfile_getnc(ptr, n, bm->remaining);
}
