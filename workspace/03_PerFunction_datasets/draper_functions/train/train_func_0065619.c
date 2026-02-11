makeCompound(Instruction *insn, bool split)
{
   LValue *rep = (split ? insn->getSrc(0) : insn->getDef(0))->asLValue();

   if (prog->dbgFlags & NV50_IR_DEBUG_REG_ALLOC) {
      INFO("makeCompound(split = %i): ", split);
      insn->print();
   }

   const unsigned int size = getNode(rep)->colors;
   unsigned int base = 0;

   if (!rep->compound)
      rep->compMask = 0xff;
   rep->compound = 1;

   for (int c = 0; split ? insn->defExists(c) : insn->srcExists(c); ++c) {
      LValue *val = (split ? insn->getDef(c) : insn->getSrc(c))->asLValue();

      val->compound = 1;
      if (!val->compMask)
         val->compMask = 0xff;
      val->compMask &= makeCompMask(size, base, getNode(val)->colors);
      assert(val->compMask);

      INFO_DBG(prog->dbgFlags, REG_ALLOC, "compound: %%%i:%02x <- %%%i:%02x\n",
           rep->id, rep->compMask, val->id, val->compMask);

      base += getNode(val)->colors;
   }
   assert(base == size);
}
