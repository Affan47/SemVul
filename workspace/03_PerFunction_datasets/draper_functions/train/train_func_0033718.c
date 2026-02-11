check_modifiable(struct StringIO *ptr)
{
    if (OBJ_FROZEN(ptr->string)) {
	rb_raise(rb_eIOError, "not modifiable string");
    }
}
