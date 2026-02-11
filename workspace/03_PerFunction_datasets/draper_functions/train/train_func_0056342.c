const_missing(VALUE klass, ID id)
{
    return rb_funcall(klass, rb_intern("const_missing"), 1, ID2SYM(id));
}
