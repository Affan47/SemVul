doCoalesce(ArrayList& insns, unsigned int mask)
{
   int c, n;

   for (n = 0; n < insns.getSize(); ++n) {
      Instruction *i;
      Instruction *insn = reinterpret_cast<Instruction *>(insns.get(n));

      switch (insn->op) {
      case OP_PHI:
         if (!(mask & JOIN_MASK_PHI))
            break;
         for (c = 0; insn->srcExists(c); ++c)
            if (!coalesceValues(insn->getDef(0), insn->getSrc(c), false)) {

               ERROR("failed to coalesce phi operands\n");
               return false;
            }
         break;
      case OP_UNION:
      case OP_MERGE:
         if (!(mask & JOIN_MASK_UNION))
            break;
         for (c = 0; insn->srcExists(c); ++c)
            coalesceValues(insn->getDef(0), insn->getSrc(c), true);
         if (insn->op == OP_MERGE) {
            merges.push_back(insn);
            if (insn->srcExists(1))
               makeCompound(insn, false);
         }
         break;
      case OP_SPLIT:
         if (!(mask & JOIN_MASK_UNION))
            break;
         splits.push_back(insn);
         for (c = 0; insn->defExists(c); ++c)
            coalesceValues(insn->getSrc(0), insn->getDef(c), true);
         makeCompound(insn, true);
         break;
      case OP_MOV:
         if (!(mask & JOIN_MASK_MOV))
            break;
         i = NULL;
         if (!insn->getDef(0)->uses.empty())
            i = insn->getDef(0)->uses.front()->getInsn();

         if (i && i->op == OP_MERGE)
            break;
         i = insn->getSrc(0)->getUniqueInsn();
         if (i && !i->constrainedDefs()) {
            if (coalesceValues(insn->getDef(0), insn->getSrc(0), false))
               copyCompound(insn->getSrc(0), insn->getDef(0));
         }
         break;
      case OP_TEX:
      case OP_TXB:
      case OP_TXL:
      case OP_TXF:
      case OP_TXQ:
      case OP_TXD:
      case OP_TXG:
      case OP_TEXCSAA:
         if (!(mask & JOIN_MASK_TEX))
            break;
         for (c = 0; insn->srcExists(c) && c != insn->predSrc; ++c)
            coalesceValues(insn->getDef(c), insn->getSrc(c), true);
         break;
      default:
         break;
      }
   }
   return true;
}
