CloneDebugInfoMetadata(Function *NewFunc, const Function *OldFunc,
                            ValueToValueMapTy &VMap) {
  DebugInfoFinder Finder;
  Finder.processModule(*OldFunc->getParent());

  const DISubprogram *OldSubprogramMDNode = FindSubprogram(OldFunc, Finder);
  if (!OldSubprogramMDNode) return;

  auto *NewSubprogram =
      cast<DISubprogram>(MapMetadata(OldSubprogramMDNode, VMap));
  NewFunc->setSubprogram(NewSubprogram);

  for (auto *CU : Finder.compile_units()) {
    auto Subprograms = CU->getSubprograms();


    for (auto *SP : Subprograms) {
      if (SP == OldSubprogramMDNode) {
        AddOperand(CU, Subprograms, NewSubprogram);
        break;
      }
    }
  }
}
