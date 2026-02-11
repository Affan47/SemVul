DoFinish() {
  DoAlternation();
  Regexp* re = stacktop_;
  if (re != NULL && re->down_ != NULL) {
    status_->set_code(kRegexpMissingParen);
    status_->set_error_arg(whole_regexp_);
    return NULL;
  }
  stacktop_ = NULL;
  return FinishRegexp(re);
}
