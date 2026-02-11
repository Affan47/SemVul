f_to_f(VALUE x)
{
    if (TYPE(x) == T_STRING)
	return DBL2NUM(rb_str_to_dbl(x, 0));
    return rb_funcall(x, id_to_f, 0);
}
