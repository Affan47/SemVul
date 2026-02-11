path_mkdir(int argc, VALUE *argv, VALUE self)
{
    VALUE str = get_strpath(self);
    VALUE vmode;
    if (rb_scan_args(argc, argv, "01", &vmode) == 0)
        return rb_funcall(rb_cDir, rb_intern("mkdir"), 1, str);
    else
        return rb_funcall(rb_cDir, rb_intern("mkdir"), 2, str, vmode);
}
