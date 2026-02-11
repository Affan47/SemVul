store(ValueMap &m, int i, int c, Value *ptr, Value *value)
{
   if (regOnly) {
      assert(!ptr);
      if (!lookup(m, i, c))
         insert(m, i, c, value);

      assert(lookup(m, i, c) == value);
   } else {
      Value *sym = lookup(m, i, c);
      if (!sym)
         sym = insert(m, i, c, mkSymbol(i, c));

      const DataType stTy = typeOfSize(value->reg.size);

      up->mkStore(OP_STORE, stTy, static_cast<Symbol *>(sym), ptr, value);
   }
}
