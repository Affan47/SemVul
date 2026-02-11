SetInputRepresentation(Representation r) {
  input_representation_ = r;
  if (r.IsTagged()) {
    SetAllSideEffects();
    ClearFlag(kUseGVN);
  } else {
    ClearAllSideEffects();
    SetFlag(kUseGVN);
  }
}
