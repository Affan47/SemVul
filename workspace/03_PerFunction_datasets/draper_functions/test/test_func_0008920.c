orderInstructions(ArrayList &result)
{
   result.clear();

   for (IteratorRef it = cfg.iteratorCFG(); !it->end(); it->next()) {
      BasicBlock *bb =
         BasicBlock::get(reinterpret_cast<Graph::Node *>(it->get()));

      for (Instruction *insn = bb->getFirst(); insn; insn = insn->next)
         result.insert(insn, insn->serial);
   }

   return result.getSize();
}
