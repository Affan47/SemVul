FindExtensionByNumber(
    const Descriptor* extendee, int number) const {
  MutexLockMaybe lock(mutex_);
  const FieldDescriptor* result = tables_->FindExtension(extendee, number);
  if (result != NULL) {
    return result;
  }
  if (underlay_ != NULL) {
    const FieldDescriptor* result =
      underlay_->FindExtensionByNumber(extendee, number);
    if (result != NULL) return result;
  }
  if (TryFindExtensionInFallbackDatabase(extendee, number)) {
    const FieldDescriptor* result = tables_->FindExtension(extendee, number);
    if (result != NULL) {
      return result;
    }
  }
  return NULL;
}
