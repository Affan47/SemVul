emitMOV(const Instruction *i)
{
   if (i->src(0).getFile() == FILE_SYSTEM_VALUE) {
      code[0] = 0x00000002 | (getSRegEncoding(i->src(0)) << 23);
      code[1] = 0x86400000;
      emitPredicate(i);
      defId(i->def(0), 2);
   } else
   if (i->src(0).getFile() == FILE_IMMEDIATE) {
      code[0] = 0x00000002 | (i->lanes << 14);
      code[1] = 0x74000000;
      emitPredicate(i);
      defId(i->def(0), 2);
      setImmediate32(i, 0, Modifier(0));
   } else
   if (i->src(0).getFile() == FILE_PREDICATE) {

   } else {
      emitForm_C(i, 0x24c, 2);
      code[1] |= i->lanes << 10;
   }
}
