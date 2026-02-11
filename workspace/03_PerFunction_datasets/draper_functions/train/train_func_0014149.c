num_negate (cpp_num num, size_t precision)
{
  cpp_num copy;

  copy = num;
  num.high = ~num.high;
  num.low = ~num.low;
  if (++num.low == 0)
    num.high++;
  num = num_trim (num, precision);
  num.overflow = (!num.unsignedp && num_eq (num, copy) && !num_zerop (num));

  return num;
}
