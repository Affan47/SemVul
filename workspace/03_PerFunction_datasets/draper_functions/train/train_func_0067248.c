emitEXPORT(const Instruction *i)
{
   uint32_t offset = i->src(0).get()->reg.data.offset;

   code[0] = 0x00000002 | (offset << 23);
   code[1] = 0x7f000000 | (offset >> 9);

#if 0
   if (i->perPatch)
      code[0] |= 0x100;
#endif

   emitPredicate(i);

   assert(i->src(1).getFile() == FILE_GPR);

   srcId(i->src(0).getIndirect(0), 10);
   srcId(i->src(0).getIndirect(1), 32 + 10);
   srcId(i->src(1), 2);
}
