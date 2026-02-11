parseTerm(PolynomialRing const &r)
{


  int c=nextNonBlank();
  if(c=='-')
    {
      c=nextNonBlank();
      ungetChar(c);
      FieldElement k(r.getField());
      k=r.getField().zHomomorphism(1);

      if(isDigit(c))
	{
	  k=parseFieldElement(r.getField());
	}
      Monomial m=parseMonomial(r);

      return Term(-k,m);
    }
  else
    {
      ungetChar(c);
      FieldElement k(r.getField());

      k=r.getField().zHomomorphism(1);


      if(isDigit(c))
	{
	  k=parseFieldElement(r.getField());
	}
      Monomial m=parseMonomial(r);

      return Term(k,m);
    }

  FieldElement k=parseFieldElement(r.getField());
  Monomial m=parseMonomial(r);


  return Term(k,m);
}
