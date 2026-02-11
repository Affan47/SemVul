AddToGlobalIdToNameMap() LOCKS_EXCLUDED(mutex) {

  CHECK(IsTemplateIdInitialized(id_));
  {

    ReaderMutexLock reader_lock(&mutex);
    if (template_string_set) {
      TemplateStringSet::const_iterator iter =
          template_string_set->find(*this);
      if (iter != template_string_set->end()) {
        DCHECK_EQ(TemplateString(ptr_, length_),
                  TemplateString(iter->ptr_, iter->length_))
            << "TemplateId collision!";
        return;
      }
    }
  }
  WriterMutexLock writer_lock(&mutex);

  if (!template_string_set) {
    template_string_set = new TemplateStringSet;
  }

  if (!arena) {
    arena = new UnsafeArena(1024);
  }

  if (template_string_set->find(*this) != template_string_set->end()) {
    return;
  }


  if (is_immutable()) {
    template_string_set->insert(*this);
  } else {
    const char* immutable_copy = arena->Memdup(ptr_, length_);
    template_string_set->insert(
        TemplateString(immutable_copy, length_, true, id_));
  }
}
