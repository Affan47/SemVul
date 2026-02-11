seed_random(uint32_t* state) {
  for (int i = 0; i < 2; ++i) {
    if (FLAG_random_seed != 0) {
      state[i] = FLAG_random_seed;
    } else if (entropy_source != NULL) {
      uint32_t val;
      ScopedLock lock(entropy_mutex);
      entropy_source(reinterpret_cast<unsigned char*>(&val), sizeof(uint32_t));
      state[i] = val;
    } else {
      state[i] = random();
    }
  }
}
