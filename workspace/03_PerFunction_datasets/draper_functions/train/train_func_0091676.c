ComputeOrder(XOTclClass *cl, XOTclClasses *order, XOTclClasses* (*direction)(XOTclClass*)) {
  if (order)
    return order;
  return cl->order = TopoOrder(cl, direction);
}
