AllocStuff() {
  void** objects = new void*[kNumObjects];
  for (int i = 0; i < kNumObjects; i++) {
    objects[i] = malloc(kObjectSize);
  }
  for (int i = 0; i < kNumObjects; i++) {
    free(objects[i]);
  }
  delete[] objects;
}
