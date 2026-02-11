leaveLocalValueArea(SavePoint OldInsertPt) {
  if (FuncInfo.InsertPt != FuncInfo.MBB->begin())
    LastLocalValue = llvm::prior(FuncInfo.InsertPt);


  FuncInfo.InsertPt = OldInsertPt.InsertPt;
  DL = OldInsertPt.DL;
}
