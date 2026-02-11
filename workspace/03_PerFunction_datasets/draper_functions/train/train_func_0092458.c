operator+(const vnl_bignum& b) const
{

  assert (! b.is_minus_infinity() || ! this->is_plus_infinity() );
  assert (! b.is_plus_infinity() || ! this->is_minus_infinity() );
  if (b.is_infinity()) { return b; }
  if (this->is_infinity()) { return *this; }

  vnl_bignum sum;
  if (this->sign == b.sign) {
    add(*this,b,sum);
    sum.sign = this->sign;
  }
  else {
    int mag = magnitude_cmp(*this,b);
    if (mag > 0) {
      subtract(*this,b,sum);
      sum.sign = this->sign;
    }
    else if (mag < 0) {
      subtract(b,*this,sum);
      sum.sign = b.sign;
    }
  }
  return sum;
}
