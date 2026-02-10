tryPropagateBranch(BasicBlock *bb)
{
   for (Instruction *i = bb->getExit(); i && i->op == OP_BRA; i = i->prev) {
      BasicBlock *bf = i->asFlow()->target.bb;

      if (bf->getInsnCount() != 1)
         continue;

      FlowInstruction *bra = i->asFlow();
      FlowInstruction *rep = bf->getExit()->asFlow();

      if (!rep || rep->getPredicate())
         continue;
      if (rep->op != OP_BRA &&
          rep->op != OP_JOIN &&
          rep->op != OP_EXIT)
         continue;


      bra->op = rep->op;
      bra->target.bb = rep->target.bb;
      if (bf->cfg.incidentCount() == 1)
         bf->remove(rep);
   }
}
