ClearFallback() {
  GOOGLE_DCHECK(fields_ != NULL);
  for (int i = 0; i < fields_->size(); i++) {
    (*fields_)[i].Delete();
  }
  fields_->clear();
}
