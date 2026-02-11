rc4InitKey(Guchar *key, int keyLen, Guchar *state) {
  Guchar index1, index2;
  Guchar t;
  int i;

  for (i = 0; i < 256; ++i)
    state[i] = i;

  if (unlikely(keyLen == 0))
    return;

  index1 = index2 = 0;
  for (i = 0; i < 256; ++i) {
    index2 = (key[index1] + state[i] + index2) % 256;
    t = state[i];
    state[i] = state[index2];
    state[index2] = t;
    index1 = (index1 + 1) % keyLen;
  }
}
