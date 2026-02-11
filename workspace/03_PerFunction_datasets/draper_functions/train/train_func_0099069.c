SimplifyInstructionsInBlock(BasicBlock *BB, const TargetData *TD) {
  bool MadeChange = false;
  for (BasicBlock::iterator BI = BB->begin(), E = BB->end(); BI != E; ) {
    Instruction *Inst = BI++;

    if (Value *V = SimplifyInstruction(Inst, TD)) {
      WeakVH BIHandle(BI);
      ReplaceAndSimplifyAllUses(Inst, V, TD);
      MadeChange = true;
      if (BIHandle != BI)
        BI = BB->begin();
      continue;
    }

    if (Inst->isTerminator())
      break;

    WeakVH BIHandle(BI);
    MadeChange |= RecursivelyDeleteTriviallyDeadInstructions(Inst);
    if (BIHandle != BI)
      BI = BB->begin();
  }
  return MadeChange;
}
