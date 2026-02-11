emitINTERP(const Instruction *i)
{
   const uint32_t base = i->getSrc(0)->reg.data.offset;

   if (i->encSize == 8) {
      code[0] = 0x00000000;
      code[1] = 0xc0000000 | (base & 0xffff);

      if (i->saturate)
         code[0] |= 1 << 5;

      if (i->op == OP_PINTERP)
         srcId(i->src(1), 26);
      else
         code[0] |= 0x3f << 26;

      srcId(i->src(0).getIndirect(0), 20);
   } else {
      assert(i->op == OP_PINTERP);
      code[0] = 0x00000009 | ((base & 0xc) << 6) | ((base >> 4) << 26);
      srcId(i->src(1), 20);
   }
   emitInterpMode(i);

   emitPredicate(i);
   defId(i->def(0), 14);

   if (i->getSampleMode() == NV50_IR_INTERP_OFFSET)
      srcId(i->src(i->op == OP_PINTERP ? 2 : 1), 17);
   else
      code[1] |= 0x3f << 17;
}
