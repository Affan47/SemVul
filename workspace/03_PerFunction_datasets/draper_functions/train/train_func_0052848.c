MixinResetOrderForInstances(Tcl_Interp *interp, XOTclClass *cl) {
  Tcl_HashSearch hSrch;
  Tcl_HashEntry *hPtr;

  hPtr = Tcl_FirstHashEntry(&cl->instances, &hSrch);


  for (; hPtr; hPtr = Tcl_NextHashEntry(&hSrch)) {
    XOTclObject *obj = (XOTclObject *)Tcl_GetHashKey(&cl->instances, hPtr);
    if (obj
        && !(obj->flags & XOTCL_DESTROY_CALLED)
        && (obj->flags & XOTCL_MIXIN_ORDER_DEFINED_AND_VALID)) {
        MixinResetOrder(obj);
        obj->flags &= ~XOTCL_MIXIN_ORDER_VALID;
    }
  }
}
