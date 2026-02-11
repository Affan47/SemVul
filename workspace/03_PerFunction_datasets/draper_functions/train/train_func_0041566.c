AddLastArg(ArgStringList &Output, OptSpecifier Id) const {
  if (Arg *A = getLastArg(Id)) {
    A->claim();
    A->render(*this, Output);
  }
}
