bug_funcall(int argc, VALUE *argv, VALUE self)
{
    if (argc < 1) rb_raise(rb_eArgError, "not enough argument");
    return rb_funcall2(self, rb_to_id(*argv), argc-1, argv+1);
}
