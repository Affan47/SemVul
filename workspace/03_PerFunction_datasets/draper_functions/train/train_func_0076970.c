ary_add_hash(VALUE hash, VALUE ary)
{
    long i;

    for (i=0; i<RARRAY_LEN(ary); i++) {
	rb_hash_aset(hash, RARRAY_PTR(ary)[i], Qtrue);
    }
    return hash;
}
