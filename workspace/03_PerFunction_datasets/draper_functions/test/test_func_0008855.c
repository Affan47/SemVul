ApproximateRetainedSizes() {


  for (int i = 0; i < snapshot_->entries()->length(); ++i) {
    HeapEntry* entry = snapshot_->entries()->at(i);
    entry->set_retained_size(entry->self_size());
  }
  for (int i = 0;
       i < snapshot_->entries()->length();
       ++i, ProgressStep()) {
    HeapEntry* entry = snapshot_->entries()->at(i);
    int entry_size = entry->self_size();
    for (HeapEntry* dominator = entry->dominator();
         dominator != entry;
         entry = dominator, dominator = entry->dominator()) {
      dominator->add_retained_size(entry_size);
    }
    if (!ProgressReport()) return false;
  }
  return true;
}
