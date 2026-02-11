runOnBasicBlock(BasicBlock &BB) {
      bool Changed = false;
      for (BasicBlock::iterator DI = BB.begin(); DI != BB.end(); ) {
        Instruction *Inst = DI++;
        if (isInstructionTriviallyDead(Inst)) {
          Inst->eraseFromParent();
          Changed = true;
          ++DIEEliminated;
        }
      }
      return Changed;
    }
