MixinSearchProc(Tcl_Interp *interp, XOTclObject *obj, char *methodName,
                XOTclClass **cl, Tcl_Command *currentCmdPtr) {
  Tcl_Command cmd = NULL;
  XOTclCmdList *cmdList;
  XOTclClass *cls;

  assert(obj);
  assert(obj->mixinStack);


  assert(obj->flags & XOTCL_MIXIN_ORDER_VALID);

  cmdList = seekCurrent(obj->mixinStack->currentCmdPtr, obj->mixinOrder);

#if defined(ACTIVEMIXIN)
  RUNTIME_STATE(interp)->cmdPtr = cmdList->cmdPtr;
#endif


  while (cmdList) {
    if (Tcl_Command_cmdEpoch(cmdList->cmdPtr)) {
      cmdList = cmdList->next;
    } else {
      cls = XOTclGetClassFromCmdPtr(cmdList->cmdPtr);


      if (cls) {
        int guardOk = TCL_OK;
        cmd = FindMethod(methodName, cls->nsPtr);
        if (cmd && cmdList->clientData) {
          if (!RUNTIME_STATE(interp)->cs.guardCount) {
            guardOk = GuardCall(obj, cls, (Tcl_Command) cmd, interp, cmdList->clientData, 1);
          }
        }
        if (cmd && guardOk == TCL_OK) {


          *cl = cls;
          *currentCmdPtr = cmdList->cmdPtr;
          break;
        } else {
          cmd = NULL;
          cmdList = cmdList->next;
        }
      }
    }
  }

  return cmd;
}
