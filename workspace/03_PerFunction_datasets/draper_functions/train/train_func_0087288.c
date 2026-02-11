checkCond(Instruction *ICI, Instruction *I, bool equal)
    {
      for (Value::use_iterator JU=ICI->use_begin(),JUE=ICI->use_end();
           JU != JUE; ++JU) {
	Value *JU_V = *JU;
        if (BranchInst *BI = dyn_cast<BranchInst>(JU_V)) {
          if (!BI->isConditional())
            continue;
          BasicBlock *S = BI->getSuccessor(equal);
          if (DT->dominates(S, I->getParent()))
            return true;
        }
        if (BinaryOperator *BI = dyn_cast<BinaryOperator>(JU_V)) {
          if (BI->getOpcode() == Instruction::Or &&
              checkCond(BI, I, equal))
            return true;
          if (BI->getOpcode() == Instruction::And &&
              checkCond(BI, I, !equal))
            return true;
        }
      }
      return false;
    }
