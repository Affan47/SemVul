emitForm_ADD(const Instruction *i)
{
   assert(i->encSize == 8);
   code[0] |= 1;

   emitFlagsRd(i);
   emitFlagsWr(i);

   setDst(i, 0);

   setSrcFileBits(i, NV50_OP_ENC_LONG_ALT);
   setSrc(i, 0, 0);
   setSrc(i, 1, 2);

   if (i->getIndirect(0, 0)) {
      assert(!i->getIndirect(1, 0));
      setAReg16(i, 0);
   } else {
      setAReg16(i, 1);
   }
}
