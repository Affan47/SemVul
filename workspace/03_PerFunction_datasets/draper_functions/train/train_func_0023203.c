operator==(const ExprValue& ev2) const {
  if(getMMIndex() != ev2.getMMIndex())
    return false;

  return (d_kind == ev2.getKind())
    && (getKids() == ev2.getKids());
}
