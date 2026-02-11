rb_struct_s_members(VALUE klass)
{
    VALUE members = struct_ivar_get(klass, id_members);

    if (NIL_P(members)) {
	rb_raise(rb_eTypeError, "uninitialized struct");
    }
    if (TYPE(members) != T_ARRAY) {
	rb_raise(rb_eTypeError, "corrupted struct");
    }
    return members;
}
