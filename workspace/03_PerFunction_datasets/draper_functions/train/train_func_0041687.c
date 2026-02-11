Equal(const FstClass &fst1, const FstClass &fst2, float delta) {
  if (!ArcTypesMatch(fst1, fst2, "Equal")) return false;

  EqualInnerArgs args(fst1, fst2, delta);
  EqualArgs args_with_retval(args);

  Apply<Operation<EqualArgs> >("Equal", fst1.ArcType(), &args_with_retval);

  return args_with_retval.retval;
}
