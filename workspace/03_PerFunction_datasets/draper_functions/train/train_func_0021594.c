StoreImageToBitMask(
    VP8LBitWriter* const bw, int width, int histo_bits,
    VP8LBackwardRefs* const refs,
    const uint16_t* histogram_symbols,
    const HuffmanTreeCode* const huffman_codes) {

  int x = 0;
  int y = 0;
  const int histo_xsize = histo_bits ? VP8LSubSampleSize(width, histo_bits) : 1;
  VP8LRefsCursor c = VP8LRefsCursorInit(refs);
  while (VP8LRefsCursorOk(&c)) {
    const PixOrCopy* const v = c.cur_pos;
    const int histogram_ix = histogram_symbols[histo_bits ?
                                               (y >> histo_bits) * histo_xsize +
                                               (x >> histo_bits) : 0];
    const HuffmanTreeCode* const codes = huffman_codes + 5 * histogram_ix;
    if (PixOrCopyIsCacheIdx(v)) {
      const int code = PixOrCopyCacheIdx(v);
      const int literal_ix = 256 + NUM_LENGTH_CODES + code;
      WriteHuffmanCode(bw, codes, literal_ix);
    } else if (PixOrCopyIsLiteral(v)) {
      static const int order[] = { 1, 2, 0, 3 };
      int k;
      for (k = 0; k < 4; ++k) {
        const int code = PixOrCopyLiteral(v, order[k]);
        WriteHuffmanCode(bw, codes + k, code);
      }
    } else {
      int bits, n_bits;
      int code, distance;

      VP8LPrefixEncode(v->len, &code, &n_bits, &bits);
      WriteHuffmanCode(bw, codes, 256 + code);
      VP8LWriteBits(bw, n_bits, bits);

      distance = PixOrCopyDistance(v);
      VP8LPrefixEncode(distance, &code, &n_bits, &bits);
      WriteHuffmanCode(bw, codes + 4, code);
      VP8LWriteBits(bw, n_bits, bits);
    }
    x += PixOrCopyLength(v);
    while (x >= width) {
      x -= width;
      ++y;
    }
    VP8LRefsCursorNext(&c);
  }
}
