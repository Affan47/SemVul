nucomp_eqeq_p(VALUE self, VALUE other)
{
    if (k_complex_p(other)) {
	get_dat2(self, other);

	return f_boolcast(f_eqeq_p(adat->real, bdat->real) &&
			  f_eqeq_p(adat->imag, bdat->imag));
    }
    if (k_numeric_p(other) && f_real_p(other)) {
	get_dat1(self);

	return f_boolcast(f_eqeq_p(dat->real, other) && f_zero_p(dat->imag));
    }
    return f_eqeq_p(other, self);
}
