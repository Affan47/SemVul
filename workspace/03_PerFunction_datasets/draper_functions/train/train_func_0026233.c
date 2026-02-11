f_format(VALUE self, VALUE (*func)(VALUE))
{
    VALUE s, impos;

    get_dat1(self);

    impos = f_tpositive_p(dat->imag);

    s = (*func)(dat->real);
    rb_str_cat2(s, !impos ? "-" : "+");

    rb_str_concat(s, (*func)(f_abs(dat->imag)));
    if (!rb_isdigit(RSTRING_PTR(s)[RSTRING_LEN(s) - 1]))
	rb_str_cat2(s, "*");
    rb_str_cat2(s, "i");

    return s;
}
