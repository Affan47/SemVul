get_gcd_abs(object x,object y) {

  object r;

  for (;;) {

    if (type_of(x) == t_fixnum && type_of(y) == t_fixnum)
      return make_fixnum(fixnum_gcd(fix(x),fix(y)));

    if (number_compare(x, y) < 0) {
      r = x;
      x = y;
      y = r;
    }
    if (type_of(y) == t_fixnum && fix(y) == 0)
      return(x);

    integer_quotient_remainder_1(x, y, NULL, &r,0);
    x = y;
    y = r;

  }

}
