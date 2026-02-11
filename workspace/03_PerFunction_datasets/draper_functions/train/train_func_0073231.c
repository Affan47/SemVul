UpdateSamplesAfterScavenge() {
  for (int i = 0; i < kSamplerWindowSize; i++) {
    Object* function = sampler_window_[i];
    if (function != NULL && isolate_->heap()->InNewSpace(function)) {
      MapWord map_word = HeapObject::cast(function)->map_word();
      if (map_word.IsForwardingAddress()) {
        sampler_window_[i] = map_word.ToForwardingAddress();
      } else {
        sampler_window_[i] = NULL;
      }
    }
  }
}
