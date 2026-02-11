updateStats(const Expr& monomial)
{
  Expr c, m;
  separateMonomial(monomial, c, m);
  updateStats(c.getRational(), m);
}
