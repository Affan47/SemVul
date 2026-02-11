lookupVirtReg(unsigned VirtReg) {
  if (UserValue *UV = virtRegToEqClass.lookup(VirtReg))
    return UV->getLeader();
  return nullptr;
}
