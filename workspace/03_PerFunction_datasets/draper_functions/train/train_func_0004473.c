RegisterPredecessor(HBasicBlock* pred) {
  if (HasPredecessor()) {


    ASSERT(IsLoopHeader() || first_ == NULL);
    HEnvironment* incoming_env = pred->last_environment();
    if (IsLoopHeader()) {
      ASSERT(phis()->length() == incoming_env->length());
      for (int i = 0; i < phis_.length(); ++i) {
        phis_[i]->AddInput(incoming_env->values()->at(i));
      }
    } else {
      last_environment()->AddIncomingEdge(this, pred->last_environment());
    }
  } else if (!HasEnvironment() && !IsFinished()) {
    ASSERT(!IsLoopHeader());
    SetInitialEnvironment(pred->last_environment()->Copy());
  }

  predecessors_.Add(pred);
}
