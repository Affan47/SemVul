DoTestSTLAlloc() {
  IntSet* x = new(initialized) IntSet[1];
  *x = IntSet(some_ints, some_ints + 6);
  for (int i = 0; i < 1000; i++) {
    x->insert(i*3);
  }
  delete [] x;
}
