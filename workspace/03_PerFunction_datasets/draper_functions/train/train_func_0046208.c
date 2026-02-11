nurat_sub(VALUE self, VALUE other)
{
    switch (TYPE(other)) {
      case T_FIXNUM:
      case T_BIGNUM:
	{
	    get_dat1(self);

	    return f_addsub(self,
			    dat->num, dat->den,
			    other, ONE, '-');
	}
      case T_FLOAT:
	return f_sub(f_to_f(self), other);
      case T_RATIONAL:
	{
	    get_dat2(self, other);

	    return f_addsub(self,
			    adat->num, adat->den,
			    bdat->num, bdat->den, '-');
	}
      default:
	return rb_num_coerce_bin(self, other, '-');
    }
}
