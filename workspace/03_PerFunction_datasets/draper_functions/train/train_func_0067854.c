NegateValue(Value *V, Instruction *BI) {
  if (Constant *C = dyn_cast<Constant>(V))
    return ConstantExpr::getNeg(C);


  if (Instruction *I = dyn_cast<Instruction>(V))
    if (I->getOpcode() == Instruction::Add && I->hasOneUse()) {

      I->setOperand(0, NegateValue(I->getOperand(0), BI));
      I->setOperand(1, NegateValue(I->getOperand(1), BI));


      I->moveBefore(BI);
      I->setName(I->getName()+".neg");
      return I;
    }


  for (Value::use_iterator UI = V->use_begin(), E = V->use_end(); UI != E;++UI){
    User *U = *UI;
    if (!BinaryOperator::isNeg(U)) continue;


    BinaryOperator *TheNeg = cast<BinaryOperator>(U);


    if (TheNeg->getParent()->getParent() != BI->getParent()->getParent())
      continue;

    BasicBlock::iterator InsertPt;
    if (Instruction *InstInput = dyn_cast<Instruction>(V)) {
      if (InvokeInst *II = dyn_cast<InvokeInst>(InstInput)) {
        InsertPt = II->getNormalDest()->begin();
      } else {
        InsertPt = InstInput;
        ++InsertPt;
      }
      while (isa<PHINode>(InsertPt)) ++InsertPt;
    } else {
      InsertPt = TheNeg->getParent()->getParent()->getEntryBlock().begin();
    }
    TheNeg->moveBefore(InsertPt);
    return TheNeg;
  }


  return BinaryOperator::CreateNeg(V, V->getName() + ".neg", BI);
}
