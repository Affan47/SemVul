path_eq(VALUE self, VALUE other)
{
    if (!rb_obj_is_kind_of(other, rb_cPathname))
        return Qfalse;
    return rb_str_equal(get_strpath(self), get_strpath(other));
}
