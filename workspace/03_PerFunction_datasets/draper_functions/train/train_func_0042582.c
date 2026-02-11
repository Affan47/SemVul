ZopfliStoreLitLenDist(unsigned short length, unsigned short dist,
                           ZopfliLZ77Store* store) {
  size_t size2 = store->size;
  ZOPFLI_APPEND_DATA(length, &store->litlens, &store->size);
  ZOPFLI_APPEND_DATA(dist, &store->dists, &size2);
}
