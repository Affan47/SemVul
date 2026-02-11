HasArgumentsParameter() {
  for (int i = 0; i < params_.length(); i++) {
    if (params_[i]->name().is_identical_to(
            isolate_->factory()->arguments_symbol())) {
      return true;
    }
  }
  return false;
}
