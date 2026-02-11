ruby_xrealloc(ptr, size)
    void *ptr;
    long size;
{
    void *mem;

    if (size < 0) {
	rb_raise(rb_eArgError, "negative re-allocation size");
    }
    if (!ptr) return xmalloc(size);
    if (size == 0) size = 1;
    malloc_increase += size;
    RUBY_CRITICAL(mem = realloc(ptr, size));
    if (!mem) {
	garbage_collect();
	RUBY_CRITICAL(mem = realloc(ptr, size));
	if (!mem) {
	    rb_memerror();
        }
    }

    return mem;
}
