emitFMUL(const Instruction *i)
{
   const int neg = (i->src(0).mod ^ i->src(1).mod).neg();

   code[0] = 0xc0000000;

   if (i->src(1).getFile() == FILE_IMMEDIATE) {
      code[1] = 0;
      emitForm_IMM(i);
      if (neg)
         code[0] |= 0x8000;
   } else
   if (i->encSize == 8) {
      code[1] = i->rnd == ROUND_Z ? 0x0000c000 : 0;
      if (neg)
         code[1] |= 0x08000000;
      emitForm_MAD(i);
   } else {
      emitForm_MUL(i);
      if (neg)
         code[0] |= 0x8000;
   }
}
