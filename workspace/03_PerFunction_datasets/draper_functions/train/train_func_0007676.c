VP8EstimateTokenSize(VP8TBuffer* const b, const uint8_t* const probas) {
  size_t size = 0;
  const VP8Tokens* p = b->pages_;
  if (b->error_) return 0;
  while (p != NULL) {
    const VP8Tokens* const next = p->next_;
    const int N = (next == NULL) ? b->left_ : 0;
    int n = MAX_NUM_TOKEN;
    while (n-- > N) {
      const uint16_t token = p->tokens_[n];
      const int bit = token & (1 << 15);
      if (token & FIXED_PROBA_BIT) {
        size += VP8BitCost(bit, token & 0xffu);
      } else {
        size += VP8BitCost(bit, probas[token & 0x3fffu]);
      }
    }
    p = next;
  }
  return size;
}
