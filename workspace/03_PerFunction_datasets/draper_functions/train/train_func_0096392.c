gcd(unsigned int a, unsigned int b) {
  if(a > b)
    return gcd(b, a);
  else if(b % a)
    return gcd(b % a, a);
  else
    return a;
}
