EliminateDuplicatePHINodes(BasicBlock *BB) {
  bool Changed = false;


  DenseMap<uintptr_t, PHINode *> HashMap;


  DenseMap<PHINode *, PHINode *> CollisionMap;


  for (BasicBlock::iterator I = BB->begin();
       PHINode *PN = dyn_cast<PHINode>(I++); ) {


    uintptr_t Hash = 0;
    for (User::op_iterator I = PN->op_begin(), E = PN->op_end(); I != E; ++I) {


      Hash ^= reinterpret_cast<uintptr_t>(static_cast<Value *>(*I));
      Hash = (Hash << 7) | (Hash >> (sizeof(uintptr_t) * CHAR_BIT - 7));
    }

    std::pair<DenseMap<uintptr_t, PHINode *>::iterator, bool> Pair =
      HashMap.insert(std::make_pair(Hash, PN));
    if (Pair.second) continue;

    for (PHINode *OtherPN = Pair.first->second; ; ) {
      if (OtherPN->isIdenticalTo(PN)) {

        PN->replaceAllUsesWith(OtherPN);
        PN->eraseFromParent();
        Changed = true;
        break;
      }

      DenseMap<PHINode *, PHINode *>::iterator I = CollisionMap.find(OtherPN);
      if (I == CollisionMap.end()) {

        PHINode *Old = Pair.first->second;
        Pair.first->second = PN;
        CollisionMap[PN] = Old;
        break;
      }

      OtherPN = I->second;
    }
  }

  return Changed;
}
