read_mpfr (FILE *fp, mpfr_ptr x, int *known_sign)
{
   int sign;
   mpfr_set_prec (x, read_mpfr_prec (fp));
   sign = nextchar;
   read_mpfr_mantissa (fp, x);


   if (known_sign != NULL)
     *known_sign =
       (!mpfr_zero_p (x) && !mpfr_inf_p (x))
       || sign == '+' || sign == '-';
}
