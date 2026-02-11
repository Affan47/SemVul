NeedsCustomLoweringPass(const GCStrategy &C) {

  return C.customWriteBarrier()
      || C.customReadBarrier()
      || C.customRoots();
}
