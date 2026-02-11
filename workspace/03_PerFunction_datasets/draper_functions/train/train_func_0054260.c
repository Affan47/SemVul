GetBackwardReferencesLowEffort(
    int width, int height, const uint32_t* const argb, int quality,
    int* const cache_bits, VP8LHashChain* const hash_chain,
    VP8LBackwardRefs refs_array[2]) {
  VP8LBackwardRefs* refs_lz77 = &refs_array[0];
  *cache_bits = 0;
  if (!BackwardReferencesLz77(width, height, argb, 0, quality,
                              1 , hash_chain, refs_lz77)) {
    return NULL;
  }
  BackwardReferences2DLocality(width, refs_lz77);
  return refs_lz77;
}
