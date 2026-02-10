initTable(void) {
  int i;

  hashSize = INITIAL_HASH_SIZE;
  while (!isPrime(hashSize)) {
    hashSize++;
  }
  buckets = (Sym **) allocate(hashSize * sizeof(Sym *));
  for (i = 0; i < hashSize; i++) {
    buckets[i] = NULL;
  }
  numEntries = 0;
}
