setAddress24(const ValueRef& src)
{
   Symbol *sym = src.get()->asSym();

   assert(sym);

   code[0] |= (sym->reg.data.offset & 0x00003f) << 26;
   code[1] |= (sym->reg.data.offset & 0xffffc0) >> 6;
}
