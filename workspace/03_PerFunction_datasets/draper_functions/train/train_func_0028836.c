erealloc(void* vp, size_t n)
{
	void *p = realloc(vp, n);
	if (p == NULL) {
		JSON_PANIC(("realloc of %u bytes failed:", n));
    }
	return p;
}
