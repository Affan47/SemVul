getAssumptionsRef() const
{
  DebugAssert(!isNull(), "CVC3::Theorem::getAssumptionsRef: we are Null");
  if (!isRefl()) {
    return thm()->getAssumptionsRef();
  }
  else return Assumptions::emptyAssump();
}
