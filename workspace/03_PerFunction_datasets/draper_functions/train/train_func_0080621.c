emitSTORE(const Instruction *i)
{
   uint32_t opc;

   switch (i->src(0).getFile()) {
   case FILE_MEMORY_GLOBAL: opc = 0x90000000; break;
   case FILE_MEMORY_LOCAL:  opc = 0xc8000000; break;
   case FILE_MEMORY_SHARED: opc = 0xc9000000; break;
   default:
      assert(!"invalid memory file");
      opc = 0;
      break;
   }
   code[0] = 0x00000005;
   code[1] = opc;

   setAddressByFile(i->src(0));
   srcId(i->src(1), 14);
   srcId(i->src(0).getIndirect(0), 20);
   if (uses64bitAddress(i))
      code[1] |= 1 << 26;

   emitPredicate(i);

   emitLoadStoreType(i->dType);
   emitCachingMode(i->cache);
}
