SimplifyFraction(int nume, int deno, int *o_nume, int *o_deno)
{
  int gcd = FindGCD2(nume, deno);
  if (gcd)
  {
    *o_nume = nume / gcd;
    *o_deno = deno / gcd;

    if (*o_deno < 0) {
      *o_nume *= -1;
      *o_deno *= -1;
    }
  }
}
