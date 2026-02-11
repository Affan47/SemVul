valid_range_p(VALUE v, int a, int b)
{
    if (FIXNUM_P(v)) {
	int vi = FIX2INT(v);
	return !(vi < a || vi > b);
    }
    return !(f_lt_p(v, INT2NUM(a)) || f_gt_p(v, INT2NUM(b)));
}
