add(char *key, Object *val) {
  dictLocker();
  if (sorted) {


    sorted = gFalse;
  }

  if (length == size) {
    if (length == 0) {
      size = 8;
    } else {
      size *= 2;
    }
    entries = (DictEntry *)greallocn(entries, size, sizeof(DictEntry));
  }
  entries[length].key = key;
  entries[length].val = *val;
  ++length;
}
