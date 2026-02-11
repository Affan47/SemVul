env_each_key(VALUE ehash)
{
    VALUE keys;
    long i;

    RETURN_ENUMERATOR(ehash, 0, 0);
    keys = env_keys();
    for (i=0; i<RARRAY_LEN(keys); i++) {
	rb_yield(RARRAY_PTR(keys)[i]);
    }
    return ehash;
}
