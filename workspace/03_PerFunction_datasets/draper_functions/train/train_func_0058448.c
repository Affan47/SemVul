__splitBoundaryList(BoundaryConditionSet& bcSet,
		    ConstReferenceCounting<PDECondition> pde,
		    ConstReferenceCounting<Boundary> b)
{
  const BoundaryList& boundaryList = dynamic_cast<const BoundaryList&>(*b);

  for (BoundaryList::List::const_iterator i = boundaryList.list().begin();
       i != boundaryList.list().end(); ++i) {
    ConstReferenceCounting<Boundary> boundary = *i;
    if (boundary->type() == Boundary::list) {
      this->__splitBoundaryList(bcSet, pde, boundary);
    } else {
      bcSet.addBoundaryCondition(new BoundaryCondition(pde, boundary));
    }
  }
}
