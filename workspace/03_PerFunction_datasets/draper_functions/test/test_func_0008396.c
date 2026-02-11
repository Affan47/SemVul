handleShadowOr(Instruction &I) {
    IRBuilder<> IRB(&I);
    ShadowAndOriginCombiner SC(this, IRB);
    for (Instruction::op_iterator OI = I.op_begin(); OI != I.op_end(); ++OI)
      SC.Add(OI->get());
    SC.Done(&I);
  }
