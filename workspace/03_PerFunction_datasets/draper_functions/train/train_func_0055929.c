strio_size(VALUE self)
{
    VALUE string = StringIO(self)->string;
    if (NIL_P(string)) {
	rb_raise(rb_eIOError, "not opened");
    }
    return ULONG2NUM(RSTRING_LEN(string));
}
