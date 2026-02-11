polyAdd(byte poly1[], byte poly2[], byte result[], int d) {
  int i;
  for(i = 0; i <= d; i++) {
    result[i] = add(poly1[i], poly2[i]);
  }
}
