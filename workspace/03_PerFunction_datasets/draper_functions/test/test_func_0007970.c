WriteModuleConstants(const ValueEnumerator &VE,
                                 BitstreamWriter &Stream) {
  const ValueEnumerator::ValueList &Vals = VE.getValues();


  for (unsigned i = 0, e = Vals.size(); i != e; ++i) {
    if (!isa<GlobalValue>(Vals[i].first)) {
      WriteConstants(i, Vals.size(), VE, Stream, true);
      return;
    }
  }
}
