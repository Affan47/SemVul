EmitALUClause(MachineBasicBlock::iterator InsertPos, ClauseFile &Clause,
      unsigned &CfCount) {
    Clause.first->getOperand(0).setImm(0);
    CounterPropagateAddr(Clause.first, CfCount);
    MachineBasicBlock *BB = Clause.first->getParent();
    BuildMI(BB, InsertPos->getDebugLoc(), TII->get(AMDGPU::ALU_CLAUSE))
        .addImm(CfCount);
    for (unsigned i = 0, e = Clause.second.size(); i < e; ++i) {
      BB->splice(InsertPos, BB, Clause.second[i]);
    }
    CfCount += Clause.second.size();
  }
