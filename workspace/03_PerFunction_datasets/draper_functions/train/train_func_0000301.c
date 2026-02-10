emitPreOp(const Instruction *i)
{
   if (i->encSize == 8) {
      emitForm_B(i, HEX64(60000000, 00000000));

      if (i->op == OP_PREEX2)
         code[0] |= 0x20;

      if (i->src(0).mod.abs()) code[0] |= 1 << 6;
      if (i->src(0).mod.neg()) code[0] |= 1 << 8;
   } else {
      emitForm_S(i, i->op == OP_PREEX2 ? 0x74000008 : 0x70000008, true);
   }
}
