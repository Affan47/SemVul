path_open(int argc, VALUE *argv, VALUE self)
{
    VALUE args[4];
    int n;

    args[0] = get_strpath(self);
    n = rb_scan_args(argc, argv, "03", &args[1], &args[2], &args[3]);
    if (rb_block_given_p()) {
        return rb_block_call(rb_cFile, rb_intern("open"), 1+n, args, 0, 0);
    }
    else {
        return rb_funcall2(rb_cFile, rb_intern("open"), 1+n, args);
    }
}
