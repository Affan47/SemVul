deleteValue(Value *PtrVal) {

  AA.deleteValue(PtrVal);


  if (Instruction *Inst = dyn_cast<Instruction>(PtrVal)) {
    if (Inst->mayReadOrWriteMemory()) {

      for (iterator I = begin(), E = end(); I != E; ++I) {
        if (I->Forward) continue;

        I->removeUnknownInst(Inst);
      }
    }
  }


  PointerMapType::iterator I = PointerMap.find(PtrVal);
  if (I == PointerMap.end()) return;


  AliasSet::PointerRec *PtrValEnt = I->second;
  AliasSet *AS = PtrValEnt->getAliasSet(*this);


  PtrValEnt->eraseFromList();


  AS->dropRef(*this);

  PointerMap.erase(I);
}
