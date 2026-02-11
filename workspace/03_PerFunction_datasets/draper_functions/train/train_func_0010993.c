rscheck(rsptr, rslen, rs)
    char *rsptr;
    long rslen;
    VALUE rs;
{
    if (RSTRING(rs)->ptr != rsptr && RSTRING(rs)->len != rslen)
	rb_raise(rb_eRuntimeError, "rs modified");
    return 1;
}
