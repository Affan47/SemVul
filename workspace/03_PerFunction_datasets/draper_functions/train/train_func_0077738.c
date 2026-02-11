rb_fix2uint(VALUE val)
{
    unsigned long num;

    if (!FIXNUM_P(val)) {
	return rb_num2uint(val);
    }
    num = FIX2ULONG(val);

    check_uint(num, rb_funcall(val, '<', 1, INT2FIX(0)));
    return num;
}
