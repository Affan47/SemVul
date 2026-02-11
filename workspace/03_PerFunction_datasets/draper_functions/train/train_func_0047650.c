ReadHuffmanCodeLengths(
    VP8LDecoder* const dec, const int* const code_length_code_lengths,
    int num_symbols, int* const code_lengths) {
  int ok = 0;
  VP8LBitReader* const br = &dec->br_;
  int symbol;
  int max_symbol;
  int prev_code_len = DEFAULT_CODE_LENGTH;
  HuffmanTree tree;

  if (!HuffmanTreeBuildImplicit(&tree, code_length_code_lengths,
                                NUM_CODE_LENGTH_CODES)) {
    dec->status_ = VP8_STATUS_BITSTREAM_ERROR;
    return 0;
  }

  if (VP8LReadBits(br, 1)) {
    const int length_nbits = 2 + 2 * VP8LReadBits(br, 3);
    max_symbol = 2 + VP8LReadBits(br, length_nbits);
    if (max_symbol > num_symbols) {
      dec->status_ = VP8_STATUS_BITSTREAM_ERROR;
      goto End;
    }
  } else {
    max_symbol = num_symbols;
  }

  symbol = 0;
  while (symbol < num_symbols) {
    int code_len;
    if (max_symbol-- == 0) break;
    VP8LFillBitWindow(br);
    code_len = ReadSymbol(&tree, br);
    if (code_len < kCodeLengthLiterals) {
      code_lengths[symbol++] = code_len;
      if (code_len != 0) prev_code_len = code_len;
    } else {
      const int use_prev = (code_len == kCodeLengthRepeatCode);
      const int slot = code_len - kCodeLengthLiterals;
      const int extra_bits = kCodeLengthExtraBits[slot];
      const int repeat_offset = kCodeLengthRepeatOffsets[slot];
      int repeat = VP8LReadBits(br, extra_bits) + repeat_offset;
      if (symbol + repeat > num_symbols) {
        dec->status_ = VP8_STATUS_BITSTREAM_ERROR;
        goto End;
      } else {
        const int length = use_prev ? prev_code_len : 0;
        while (repeat-- > 0) code_lengths[symbol++] = length;
      }
    }
  }
  ok = 1;

 End:
  HuffmanTreeRelease(&tree);
  return ok;
}
