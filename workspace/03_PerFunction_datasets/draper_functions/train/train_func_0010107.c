GenerateDeferredCode() {
  ASSERT(is_generating());
  for (int i = 0; !is_aborted() && i < deferred_.length(); i++) {
    LDeferredCode* code = deferred_[i];
    __ bind(code->entry());
    code->Generate();
    __ jmp(code->exit());
  }


  if (!is_aborted()) status_ = DONE;
  return !is_aborted();
}
