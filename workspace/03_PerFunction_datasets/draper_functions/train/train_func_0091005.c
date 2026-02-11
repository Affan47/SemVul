OptimizeCmpExpression(CmpInst *CI) {
  BasicBlock *DefBB = CI->getParent();


  DenseMap<BasicBlock*, CmpInst*> InsertedCmps;

  bool MadeChange = false;
  for (Value::use_iterator UI = CI->use_begin(), E = CI->use_end();
       UI != E; ) {
    Use &TheUse = UI.getUse();
    Instruction *User = cast<Instruction>(*UI);


    ++UI;


    if (isa<PHINode>(User))
      continue;


    BasicBlock *UserBB = User->getParent();


    if (UserBB == DefBB) continue;


    CmpInst *&InsertedCmp = InsertedCmps[UserBB];

    if (!InsertedCmp) {
      BasicBlock::iterator InsertPt = UserBB->getFirstInsertionPt();
      InsertedCmp =
        CmpInst::Create(CI->getOpcode(),
                        CI->getPredicate(),  CI->getOperand(0),
                        CI->getOperand(1), "", InsertPt);
      MadeChange = true;
    }


    TheUse = InsertedCmp;
    ++NumCmpUses;
  }


  if (CI->use_empty())
    CI->eraseFromParent();

  return MadeChange;
}
