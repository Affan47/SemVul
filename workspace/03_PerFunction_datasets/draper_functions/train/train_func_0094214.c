PrepareForBailoutBeforeSplit(State state,
                                                     bool should_normalize,
                                                     Label* if_true,
                                                     Label* if_false) {


  if (!context()->IsTest() || !info_->IsOptimizable()) return;

  NearLabel skip;
  if (should_normalize) __ jmp(&skip);

  ForwardBailoutStack* current = forward_bailout_stack_;
  while (current != NULL) {
    PrepareForBailout(current->expr(), state);
    current = current->parent();
  }

  if (should_normalize) {
    __ CompareRoot(rax, Heap::kTrueValueRootIndex);
    Split(equal, if_true, if_false, NULL);
    __ bind(&skip);
  }
}
