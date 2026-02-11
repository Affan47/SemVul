Lookup(void* key, uint32_t hash, bool insert) {

  Entry* p = Probe(key, hash);
  if (p->key != NULL) {
    return p;
  }


  if (insert) {
    p->key = key;
    p->value = NULL;
    p->hash = hash;
    occupancy_++;


    if (occupancy_ + occupancy_/4 >= capacity_) {
      Resize();
      p = Probe(key, hash);
    }

    return p;
  }


  return NULL;
}
