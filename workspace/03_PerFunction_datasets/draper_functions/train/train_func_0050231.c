cdhash_hash(VALUE a)
{
    if (SPECIAL_CONST_P(a)) return (st_index_t)a;
    if (TYPE(a) == T_STRING) return rb_str_hash(a);
    {
	VALUE hval = rb_hash(a);
	return (st_index_t)FIX2LONG(hval);
    }
}
