assignSlot(const Interval &livei, const unsigned int size)
{
   SpillSlot slot;
   int32_t offsetBase = stackSize;
   int32_t offset;
   std::list<SpillSlot>::iterator pos = slots.end(), it = slots.begin();

   if (offsetBase % size)
      offsetBase += size - (offsetBase % size);

   slot.sym = NULL;

   for (offset = offsetBase; offset < stackSize; offset += size) {
      const int32_t entryEnd = offset + size;
      while (it != slots.end() && it->offset < offset)
         ++it;
      if (it == slots.end())
         break;
      std::list<SpillSlot>::iterator bgn = it;

      while (it != slots.end() && it->offset < entryEnd) {
         it->occup.print();
         if (it->occup.overlaps(livei))
            break;
         ++it;
      }
      if (it == slots.end() || it->offset >= entryEnd) {

         for (; bgn != slots.end() && bgn->offset < entryEnd; ++bgn) {
            bgn->occup.insert(livei);
            if (bgn->size() == size)
               slot.sym = bgn->sym;
         }
         break;
      }
   }
   if (!slot.sym) {
      stackSize = offset + size;
      slot.offset = offset;
      slot.sym = new_Symbol(func->getProgram(), FILE_MEMORY_LOCAL);
      if (!func->stackPtr)
         offset += func->tlsBase;
      slot.sym->setAddress(NULL, offset);
      slot.sym->reg.size = size;
      slots.insert(pos, slot)->occup.insert(livei);
   }
   return slot.sym;
}
