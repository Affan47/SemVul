operator*=(long r)
{
  long a = vnl_rational::gcd(r,den_);
  den_ /= a; r /= a;

  double n = double(r) * double(num_);
  if (n < vnl_numeric_traits<long>::maxval)
  { num_ *= r; normalize(); return *this; }
  else
    return *this = vnl_rational(n/double(den_));
}
