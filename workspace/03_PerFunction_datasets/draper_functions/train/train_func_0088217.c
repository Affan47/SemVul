emitFMUL(const Instruction *i)
{
   bool neg = (i->src(0).mod ^ i->src(1).mod).neg();

   assert(i->postFactor >= -3 && i->postFactor <= 3);

   if (i->encSize == 8) {
      if (isLIMM(i->src(1), TYPE_F32)) {
         assert(i->postFactor == 0);
         emitForm_A(i, HEX64(30000000, 00000002));
      } else {
         emitForm_A(i, HEX64(58000000, 00000000));
         roundMode_A(i);
         code[1] |= ((i->postFactor > 0) ?
                     (7 - i->postFactor) : (0 - i->postFactor)) << 17;
      }
      if (neg)
         code[1] ^= 1 << 25;

      if (i->saturate)
         code[0] |= 1 << 5;

      if (i->dnz)
         code[0] |= 1 << 7;
      else
      if (i->ftz)
         code[0] |= 1 << 6;
   } else {
      assert(!neg && !i->saturate && !i->ftz && !i->postFactor);
      emitForm_S(i, 0xa8, true);
   }
}
