gcd(u32 a, u32 b)
{
  if (a && b)
  {
    while (a && b)
    {
      if (a>b)
      {
        a = a%b;
      }
      else
      {
        b = b%a;
      }
    }

    return a+b;
  }
  else
  {
    return 0;
  }
}
