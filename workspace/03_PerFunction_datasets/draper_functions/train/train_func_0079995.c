get_char_digit_x_from_int(int i, int place)
{
  int n,a,divisor;
  n = int_ndigits(i);

  if(n < place) return digit_to_char(0);

  divisor = 1;
  for(a = 0; a < (place-1); a++) divisor *= 10;

  i %= (divisor*10);
  return digit_to_char (i / divisor);
}
