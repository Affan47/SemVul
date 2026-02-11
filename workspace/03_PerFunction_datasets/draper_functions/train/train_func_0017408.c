getGlobalValueAtAddress(void *Addr) {
  MutexGuard locked(lock);


  if (EEState.getGlobalAddressReverseMap().empty()) {
    for (ExecutionEngineState::GlobalAddressMapTy::iterator
           I = EEState.getGlobalAddressMap().begin(),
           E = EEState.getGlobalAddressMap().end(); I != E; ++I) {
      StringRef Name = I->first();
      uint64_t Addr = I->second;
      EEState.getGlobalAddressReverseMap().insert(std::make_pair(
                                                          Addr, Name));
    }
  }

  std::map<uint64_t, std::string>::iterator I =
    EEState.getGlobalAddressReverseMap().find((uint64_t) Addr);

  if (I != EEState.getGlobalAddressReverseMap().end()) {
    StringRef Name = I->second;
    for (unsigned i = 0, e = Modules.size(); i != e; ++i)
      if (GlobalValue *GV = Modules[i]->getNamedValue(Name))
        return GV;
  }
  return nullptr;
}
