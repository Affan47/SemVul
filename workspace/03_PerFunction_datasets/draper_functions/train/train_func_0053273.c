PutI16Mode(VP8BitWriter* const bw, int mode) {
  if (VP8PutBit(bw, (mode == TM_PRED || mode == H_PRED), 156)) {
    VP8PutBit(bw, mode == TM_PRED, 128);
  } else {
    VP8PutBit(bw, mode == V_PRED, 163);
  }
}
