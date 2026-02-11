set_arg0(VALUE val, ID id)
{
    char *s;
    long i;

    if (origarg.argv == 0)
	rb_raise(rb_eRuntimeError, "$0 not initialized");
    StringValue(val);
    s = RSTRING_PTR(val);
    i = RSTRING_LEN(val);

    setproctitle("%.*s", (int)i, s);

    rb_progname = rb_obj_freeze(rb_external_str_new(s, i));
}
