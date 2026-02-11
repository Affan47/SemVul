New(JSFunction* function,
                              BailoutType type,
                              unsigned bailout_id,
                              Address from,
                              int fp_to_sp_delta) {
  Deoptimizer* deoptimizer =
      new Deoptimizer(function, type, bailout_id, from, fp_to_sp_delta);
  ASSERT(current_ == NULL);
  current_ = deoptimizer;
  return deoptimizer;
}
