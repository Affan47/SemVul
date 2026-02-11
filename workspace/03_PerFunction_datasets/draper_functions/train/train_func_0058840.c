tryPredicateConditional(BasicBlock *bb)
{
   BasicBlock *bL = NULL, *bR = NULL;
   unsigned int nL = 0, nR = 0, limit = 12;
   Instruction *insn;
   unsigned int mask;

   mask = bb->initiatesSimpleConditional();
   if (!mask)
      return false;

   assert(bb->getExit());
   Value *pred = bb->getExit()->getPredicate();
   assert(pred);

   if (isConstantCondition(pred))
      limit = 4;

   Graph::EdgeIterator ei = bb->cfg.outgoing();

   if (mask & 1) {
      bL = BasicBlock::get(ei.getNode());
      for (insn = bL->getEntry(); insn; insn = insn->next, ++nL)
         if (!mayPredicate(insn, pred))
            return false;
      if (nL > limit)
         return false;
   }
   ei.next();

   if (mask & 2) {
      bR = BasicBlock::get(ei.getNode());
      for (insn = bR->getEntry(); insn; insn = insn->next, ++nR)
         if (!mayPredicate(insn, pred))
            return false;
      if (nR > limit)
         return false;
   }

   if (bL)
      predicateInstructions(bL, pred, bb->getExit()->cc);
   if (bR)
      predicateInstructions(bR, pred, inverseCondCode(bb->getExit()->cc));

   if (bb->joinAt) {
      bb->remove(bb->joinAt);
      bb->joinAt = NULL;
   }
   removeFlow(bb->getExit());


   if (prog->getTarget()->joinAnterior) {
      bb = BasicBlock::get((bL ? bL : bR)->cfg.outgoing().getNode());
      if (bb->getEntry() && bb->getEntry()->op == OP_JOIN)
         removeFlow(bb->getEntry());
   }

   return true;
}
