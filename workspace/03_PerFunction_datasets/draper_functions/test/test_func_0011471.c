check_load_arg(struct load_arg *arg, ID sym)
{
    if (!arg->symbols) {
        rb_raise(rb_eRuntimeError, "Marshal.load reentered at %s",
		 rb_id2name(sym));
    }
}
