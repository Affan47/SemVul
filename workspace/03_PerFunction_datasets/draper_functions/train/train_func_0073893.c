power_mod(int n, int m, int p)
{
     if (m == 0)
	  return 1;
     else if (m % 2 == 0) {
	  int x = power_mod(n, m / 2, p);
	  return MULMOD(x, x, p);
     }
     else
	  return MULMOD(n, power_mod(n, m - 1, p), p);
}
