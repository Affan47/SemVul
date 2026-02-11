replaceZero(Instruction *i)
{
   for (int s = 0; i->srcExists(s); ++s) {
      ImmediateValue *imm = i->getSrc(s)->asImm();
      if (imm && imm->reg.data.u64 == 0)
         i->setSrc(s, r63);
   }
}
