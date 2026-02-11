SearchDefaultValues(Tcl_Interp *interp, XOTclObject *obj, XOTclClass *cmdCl) {
  XOTcl_FrameDecls;
  XOTclClass *cl = obj->cl, *mixin;
  XOTclClasses *pl;
  XOTclCmdList *ml;
  int result = TCL_OK;

  if (!(obj->flags & XOTCL_MIXIN_ORDER_VALID))
    MixinComputeDefined(interp, obj);
  if (obj->flags & XOTCL_MIXIN_ORDER_DEFINED_AND_VALID)
    ml = obj->mixinOrder;
  else
    ml = NULL;

  assert(cl);

  XOTcl_PushFrame(interp, obj);

  while (ml) {
    mixin = XOTclGetClassFromCmdPtr(ml->cmdPtr);
    result = SearchDefaultValuesOnClass(interp, obj, cmdCl, mixin);
    if (result != TCL_OK)
      break;
    ml = ml->next;
  }

  for (pl = ComputeOrder(cl, cl->order, Super); pl; pl = pl->next) {
    result = SearchDefaultValuesOnClass(interp, obj, cmdCl, pl->cl);
    if (result != TCL_OK)
      break;
  }

  XOTcl_PopFrame(interp, obj);
  return result;
}
