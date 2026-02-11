placeCSRSpillsAndRestores(MachineFunction &Fn) {

  DEBUG(MF = &Fn);

  initShrinkWrappingInfo();

  DEBUG(if (ShrinkWrapThisFunction) {
      dbgs() << "Place CSR spills/restores for "
             << MF->getFunction()->getName() << "\n";
    });

  if (calculateSets(Fn))
    placeSpillsAndRestores(Fn);
}
