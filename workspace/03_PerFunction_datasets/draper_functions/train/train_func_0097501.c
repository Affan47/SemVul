emitCSpecificHandlerTable(const MachineFunction *MF) {
  auto &OS = *Asm->OutStreamer;
  MCContext &Ctx = Asm->OutContext;

  WinEHFuncInfo &FuncInfo = MMI->getWinEHFuncInfo(MF->getFunction());


  MCSymbol *TableBegin =
      Ctx.createTempSymbol("lsda_begin", true);
  MCSymbol *TableEnd =
      Ctx.createTempSymbol("lsda_end", true);
  const MCExpr *LabelDiff = getOffset(TableEnd, TableBegin);
  const MCExpr *EntrySize = MCConstantExpr::create(16, Ctx);
  const MCExpr *EntryCount = MCBinaryExpr::createDiv(LabelDiff, EntrySize, Ctx);
  OS.EmitValue(EntryCount, 4);

  OS.EmitLabel(TableBegin);


  const MCSymbol *LastStartLabel = nullptr;
  int LastEHState = -1;


  MachineFunction::const_iterator End = MF->end();
  MachineFunction::const_iterator Stop = std::next(MF->begin());
  while (Stop != End && !Stop->isEHFuncletEntry())
    ++Stop;
  for (const auto &StateChange :
       InvokeStateChangeIterator::range(FuncInfo, MF->begin(), Stop)) {


    if (LastEHState != -1)
      emitSEHActionsForRange(FuncInfo, LastStartLabel,
                             StateChange.PreviousEndLabel, LastEHState);
    LastStartLabel = StateChange.NewStartLabel;
    LastEHState = StateChange.NewState;
  }

  OS.EmitLabel(TableEnd);
}
