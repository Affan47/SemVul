Simplify() {
  if (op_ != AND && op_ != OR) {
    return this;
  }


  if (subs_->size() == 0) {
    if (op_ == AND)
      op_ = ALL;
    else
      op_ = NONE;

    return this;
  }


  if (subs_->size() == 1) {
    Prefilter* a = (*subs_)[0];
    subs_->clear();
    delete this;
    return a->Simplify();
  }

  return this;
}
