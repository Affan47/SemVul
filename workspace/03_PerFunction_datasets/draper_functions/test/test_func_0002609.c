PopInst(std::vector<SUnit *> &Q, bool AnyALU) {
  if (Q.empty())
    return nullptr;
  for (std::vector<SUnit *>::reverse_iterator It = Q.rbegin(), E = Q.rend();
      It != E; ++It) {
    SUnit *SU = *It;
    InstructionsGroupCandidate.push_back(SU->getInstr());
    if (TII->fitsConstReadLimitations(InstructionsGroupCandidate)
        && (!AnyALU || !TII->isVectorOnly(SU->getInstr()))
    ) {
      InstructionsGroupCandidate.pop_back();
      Q.erase((It + 1).base());
      return SU;
    } else {
      InstructionsGroupCandidate.pop_back();
    }
  }
  return nullptr;
}
