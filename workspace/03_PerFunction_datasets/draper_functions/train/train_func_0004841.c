emitBinary(struct nv50_ir_prog_info *info)
{
   CodeEmitter *emit = target->getCodeEmitter(progType);

   emit->prepareEmission(this);

   if (dbgFlags & NV50_IR_DEBUG_BASIC)
      this->print();

   if (!binSize) {
      code = NULL;
      return false;
   }
   code = reinterpret_cast<uint32_t *>(MALLOC(binSize));
   if (!code)
      return false;
   emit->setCodeLocation(code, binSize);

   for (ArrayList::Iterator fi = allFuncs.iterator(); !fi.end(); fi.next()) {
      Function *fn = reinterpret_cast<Function *>(fi.get());

      assert(emit->getCodeSize() == fn->binPos);

      for (int b = 0; b < fn->bbCount; ++b)
         for (Instruction *i = fn->bbArray[b]->getEntry(); i; i = i->next)
            emit->emitInstruction(i);
   }
   info->bin.relocData = emit->getRelocInfo();

   emitSymbolTable(info);


   if ((dbgFlags & NV50_IR_DEBUG_BASIC) && getTarget()->getChipset() < 0xc0)
      emit->printBinary();

   delete emit;
   return true;
}
