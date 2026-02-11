massEquation(PolynomialRing const &r, int N, bool withMasses, bool saturate)
{
  Polynomial ret(r);
  for(int i=0;i<N;i++)
    for(int j=0;j<i;j++)
      {
	Polynomial mm=r.one();
	if(withMasses)mm=Polynomial(Term(r.getField().zHomomorphism(1),Monomial(r,IntegerVector::standardVector(r.getNumberOfVariables(),i)+IntegerVector::standardVector(r.getNumberOfVariables(),j))));
	ret+=(rPolynomial(r,N,withMasses,i,j,2)-rPolynomial(r,N,withMasses,i,j,-1))*mm;
      }
  if(saturate)ret.saturate();
  return ret;
}
