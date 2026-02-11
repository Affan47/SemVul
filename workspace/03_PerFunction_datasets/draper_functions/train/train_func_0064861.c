StoreImageToBitMask(
    VP8LBitWriter* const bw, int width, int histo_bits,
    VP8LBackwardRefs* const refs,
    const uint16_t* histogram_symbols,
    const HuffmanTreeCode* const huffman_codes) {
  const int histo_xsize = histo_bits ? VP8LSubSampleSize(width, histo_bits) : 1;
  const int tile_mask = (histo_bits == 0) ? 0 : -(1 << histo_bits);

  int x = 0;
  int y = 0;
  int tile_x = x & tile_mask;
  int tile_y = y & tile_mask;
  int histogram_ix = histogram_symbols[0];
  const HuffmanTreeCode* codes = huffman_codes + 5 * histogram_ix;
  VP8LRefsCursor c = VP8LRefsCursorInit(refs);
  while (VP8LRefsCursorOk(&c)) {
    const PixOrCopy* const v = c.cur_pos;
    if ((tile_x != (x & tile_mask)) || (tile_y != (y & tile_mask))) {
      tile_x = x & tile_mask;
      tile_y = y & tile_mask;
      histogram_ix = histogram_symbols[(y >> histo_bits) * histo_xsize +
                                       (x >> histo_bits)];
      codes = huffman_codes + 5 * histogram_ix;
    }
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
      VP8LPutBits(bw, bits, n_bits);

      distance = PixOrCopyDistance(v);
      VP8LPrefixEncode(distance, &code, &n_bits, &bits);
      WriteHuffmanCode(bw, codes + 4, code);
      VP8LPutBits(bw, bits, n_bits);
    }
    x += PixOrCopyLength(v);
    while (x >= width) {
      x -= width;
      ++y;
    }
    VP8LRefsCursorNext(&c);
  }
  return bw->error_ ? VP8_ENC_ERROR_OUT_OF_MEMORY : VP8_ENC_OK;
}
