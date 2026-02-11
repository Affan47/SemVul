nurat_truncate(VALUE self)
{
    get_dat1(self);
    if (f_negative_p(dat->num))
	return f_negate(f_idiv(f_negate(dat->num), dat->den));
    return f_idiv(dat->num, dat->den);
}
