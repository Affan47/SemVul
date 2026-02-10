polynomialToFraction(Polynomial const &p)
{
  FieldRationalFunctions2Implementation *imp=dynamic_cast<FieldRationalFunctions2Implementation*>(implementingObject);
  Polynomial q=Term(imp->getPolynomialRing().getField().zHomomorphism(1),Monomial(imp->getPolynomialRing()));

  return new FieldElementRationalFunction2(*imp, p, q);
}
