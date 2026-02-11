getScopeNode(DebugLoc DL, const LLVMContext &Ctx) {
  if (MDNode *InlinedAt = DL.getInlinedAt(Ctx))
    return getScopeNode(DebugLoc::getFromDILocation(InlinedAt), Ctx);
  return DL.getScope(Ctx);
}
