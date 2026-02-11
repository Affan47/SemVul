parsePolynomial(PolynomialRing const &r)
{


  bool first=true;
  Polynomial p(r);
  Monomial firstMonomial(r);


  while(true)
    {

      int c=nextNonBlank();


      ungetChar(c);

      if(isDigit(c)|| c=='+' || c=='-' || isVariable(c))
        {

          if(c=='+')nextNonBlank();
	  Term t=parseTerm(r);
	  if(!t.c.isZero())
	  {
	    if(first)
	      {
		firstMonomial=t.m;
		first=false;
	      }

	    Polynomial q=Polynomial(t);


	    p+=q;

	  }
        }
      else
        break;
    }


  if(!first)
    {
      firstMonomial.exponent.resize(p.getNumberOfVariables());
      p.mark(firstMonomial);

    }


  return p;
}
