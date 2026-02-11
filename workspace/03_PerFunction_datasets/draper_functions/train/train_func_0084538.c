LookupSample(JSFunction* function) {
  int weight = 0;
  for (int i = 0; i < kSamplerWindowSize; i++) {
    Object* sample = sampler_window_[i];
    if (sample != NULL) {
      if (function == sample) {
        weight += sampler_window_weight_[i];
      }
    }
  }
  return weight;
}
