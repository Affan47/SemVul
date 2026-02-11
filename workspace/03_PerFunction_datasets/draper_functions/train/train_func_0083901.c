struct_alloc(VALUE klass)
{
    long n;
    NEWOBJ(st, struct RStruct);
    OBJSETUP(st, klass, T_STRUCT);

    n = num_members(klass);

    if (0 < n && n <= RSTRUCT_EMBED_LEN_MAX) {
        RBASIC(st)->flags &= ~RSTRUCT_EMBED_LEN_MASK;
        RBASIC(st)->flags |= n << RSTRUCT_EMBED_LEN_SHIFT;
	rb_mem_clear(st->as.ary, n);
    }
    else {
	st->as.heap.ptr = ALLOC_N(VALUE, n);
	rb_mem_clear(st->as.heap.ptr, n);
	st->as.heap.len = n;
    }

    return (VALUE)st;
}
