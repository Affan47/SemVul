RemoveFromInstmixins(Tcl_Command cmd, XOTclCmdList *cmdlist) {
  for ( ; cmdlist; cmdlist = cmdlist->next) {
    XOTclClass *cl = XOTclGetClassFromCmdPtr(cmdlist->cmdPtr);
    XOTclClassOpt *clopt = cl ? cl->opt : NULL;
    if (clopt) {
      XOTclCmdList *del = CmdListFindCmdInList(cmd, clopt->instmixins);
      if (del) {


        del = CmdListRemoveFromList(&clopt->instmixins, del);
        CmdListDeleteCmdListEntry(del, GuardDel);
	if (cl->object.mixinOrder) MixinResetOrder(&cl->object);
      }
    }
  }
}
