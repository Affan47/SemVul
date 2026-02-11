doesEHPadUnwindToCaller(const Instruction *EHPad) {
  auto *CPI = dyn_cast<CleanupPadInst>(EHPad);
  if (!CPI)
    return EHPad->mayThrow();


  if (CPI->use_empty())
    return true;

  const Instruction *User = CPI->user_back();
  if (auto *CRI = dyn_cast<CleanupReturnInst>(User))
    return CRI->unwindsToCaller();
  return cast<CleanupEndPadInst>(User)->unwindsToCaller();
}
