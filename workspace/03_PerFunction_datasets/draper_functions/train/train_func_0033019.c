divide_aux(const vnl_bignum& b1, Data d, vnl_bignum& q, Data& r)
{
  r = 0;
  unsigned long temp;
  for (Counter j = b1.count; j > 0; j--) {
    temp = (unsigned long)r*0x10000L + (unsigned long)b1.data[j - 1];
    if (j < 1 + q.count)
      q.data[j - 1] = Data(temp/d);
    r = Data(temp % d);
  }
}
