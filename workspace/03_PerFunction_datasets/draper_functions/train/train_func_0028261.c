get_freefunc(VALUE func, volatile VALUE *wrap)
{
    VALUE addrnum;
    if (NIL_P(func)) {
	*wrap = 0;
	return NULL;
    }
    if (rb_dlcfunc_kind_p(func)) {
	*wrap = func;
	return (freefunc_t)(VALUE)RCFUNC_DATA(func)->ptr;
    }
    addrnum = rb_Integer(func);
    *wrap = (addrnum != func) ? func : 0;
    return (freefunc_t)(VALUE)NUM2PTR(addrnum);
}
