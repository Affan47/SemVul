sum(Subspace const &a, Subspace const &b)
{


   Subspace ret=a;
  ret.basis2=combineOnTop(a.basis2,b.basis2);
  ret.basis2.reduce();
  ret.basis2.REformToRREform();
  ret.basis2.scaleFirstNonZeroEntryToOne();
  ret.basis2.removeZeroRows();

  ret.integerRep=ret.getRepresentation();
  ret.integerRep.sort();

  return ret;
}
