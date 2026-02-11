computeGlobalGOTEquivs(Module &M) {
  if (!getObjFileLowering().supportIndirectSymViaGOTPCRel())
    return;

  for (const auto &G : M.globals()) {
    unsigned NumGOTEquivUsers = 0;
    if (!isGOTEquivalentCandidate(&G, NumGOTEquivUsers))
      continue;

    const MCSymbol *GOTEquivSym = getSymbol(&G);
    GlobalGOTEquivs[GOTEquivSym] = std::make_pair(&G, NumGOTEquivUsers);
  }
}
