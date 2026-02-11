jisx0301_date(VALUE jd, VALUE y)
{
    VALUE a[2];

    if (f_lt_p(jd, INT2FIX(2405160)))
	return rb_usascii_str_new2("%Y-%m-%d");
    if (f_lt_p(jd, INT2FIX(2419614))) {
	a[0] = rb_usascii_str_new2("M%02d" ".%%m.%%d");
	a[1] = f_sub(y, INT2FIX(1867));
    }
    else if (f_lt_p(jd, INT2FIX(2424875))) {
	a[0] = rb_usascii_str_new2("T%02d" ".%%m.%%d");
	a[1] = f_sub(y, INT2FIX(1911));
    }
    else if (f_lt_p(jd, INT2FIX(2447535))) {
	a[0] = rb_usascii_str_new2("S%02d" ".%%m.%%d");
	a[1] = f_sub(y, INT2FIX(1925));
    }
    else {
	a[0] = rb_usascii_str_new2("H%02d" ".%%m.%%d");
	a[1] = f_sub(y, INT2FIX(1988));
    }
    return rb_f_sprintf(2, a);
}
