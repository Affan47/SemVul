exc_to_s(VALUE exc)
{
    VALUE mesg = rb_attr_get(exc, rb_intern("mesg"));
    VALUE r = Qnil;

    if (NIL_P(mesg)) return rb_class_name(CLASS_OF(exc));
    r = rb_String(mesg);
    return r;
}
