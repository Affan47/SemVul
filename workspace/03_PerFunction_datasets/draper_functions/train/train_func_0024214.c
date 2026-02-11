replace(GooString *key, void *val) {
  GooHashBucket *p;
  int h;

  if ((p = find(key, &h))) {
    p->val.p = val;
    if (deleteKeys) {
      delete key;
    }
  } else {
    add(key, val);
  }
}
