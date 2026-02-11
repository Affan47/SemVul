NextSearchMethod(XOTclObject *obj, Tcl_Interp *interp, XOTclCallStackContent *csc,
                 XOTclClass **cl, char **method, Tcl_Command *cmd,
                 int *isMixinEntry, int *isFilterEntry,
                 int *endOfFilterChain, Tcl_Command *currentCmd) {
  XOTclClasses *pl = 0;
  int endOfChain = 0;

  *endOfFilterChain = 0;


  FilterComputeDefined(interp, obj);

  if ((obj->flags & XOTCL_FILTER_ORDER_VALID) &&
      obj->filterStack &&
      obj->filterStack->currentCmdPtr) {
    *cmd = FilterSearchProc(interp, obj, currentCmd, cl);


    if (*cmd == 0) {
      if (csc->frameType == XOTCL_CSC_TYPE_ACTIVE_FILTER) {


        *method = ObjStr(obj->filterStack->calledProc);
        endOfChain = 1;
        *endOfFilterChain = 1;
        *cl = 0;

      }
    } else {
      *method = (char *) Tcl_GetCommandName(interp, *cmd);
      *isFilterEntry = 1;
      return;
    }
  }


  assert(obj->flags & XOTCL_MIXIN_ORDER_VALID);


  if ((obj->flags & XOTCL_MIXIN_ORDER_VALID) &&  obj->mixinStack) {
    *cmd = MixinSearchProc(interp, obj, *method, cl, currentCmd);

    if (*cmd == 0) {
      if (csc->frameType == XOTCL_CSC_TYPE_ACTIVE_MIXIN) {
        endOfChain = 1;
        *cl = 0;
      }
    } else {
      *isMixinEntry = 1;
      return;
    }
  }


  if (obj->nsPtr && endOfChain) {
    *cmd = FindMethod(*method, obj->nsPtr);
  } else {
    *cmd = 0;
  }


  if (!*cmd) {
    for (pl = ComputeOrder(obj->cl, obj->cl->order, Super); pl && *cl; pl = pl->next) {
      if (pl->cl == *cl)
        *cl = 0;
    }


    *cl = SearchPLMethod(pl, *method, cmd);

  } else {
    *cl = 0;
  }

  return;
}
