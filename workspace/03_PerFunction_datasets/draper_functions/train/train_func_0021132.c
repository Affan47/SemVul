run(const std::list<ValuePair>& lst)
{
   for (std::list<ValuePair>::const_iterator it = lst.begin(); it != lst.end();
        ++it) {
      LValue *lval = it->first->asLValue();
      Symbol *mem = it->second ? it->second->asSym() : NULL;

      for (Value::DefIterator d = lval->defs.begin(); d != lval->defs.end();
           ++d) {
         Value *slot = mem ?
            static_cast<Value *>(mem) : new_LValue(func, FILE_GPR);
         Value *tmp = NULL;
         Instruction *last = NULL;

         LValue *dval = (*d)->get()->asLValue();
         Instruction *defi = (*d)->getInsn();


         while (!dval->uses.empty()) {
            ValueRef *u = dval->uses.front();
            Instruction *usei = u->getInsn();
            assert(usei);
            if (usei->isPseudo()) {
               tmp = (slot->reg.file == FILE_MEMORY_LOCAL) ? NULL : slot;
               last = NULL;
            } else
            if (!last || usei != last->next) {
               tmp = unspill(usei, dval, slot);
               last = usei;
            }
            u->set(tmp);
         }

         assert(defi);
         if (defi->isPseudo()) {
            d = lval->defs.erase(d);
            --d;
            if (slot->reg.file == FILE_MEMORY_LOCAL)
               delete_Instruction(func->getProgram(), defi);
            else
               defi->setDef(0, slot);
         } else {
            spill(defi, slot, dval);
         }
      }

   }


   stackBase = stackSize;
   slots.clear();
   return true;
}
