ReconstructIntra16(VP8EncIterator* const it,
                              VP8ModeScore* const rd,
                              uint8_t* const yuv_out,
                              int mode) {
  const VP8Encoder* const enc = it->enc_;
  const uint8_t* const ref = it->yuv_p_ + VP8I16ModeOffsets[mode];
  const uint8_t* const src = it->yuv_in_ + Y_OFF;
  const VP8SegmentInfo* const dqm = &enc->dqm_[it->mb_->segment_];
  int nz = 0;
  int n;
  int16_t tmp[16][16], dc_tmp[16];

  for (n = 0; n < 16; ++n) {
    VP8FTransform(src + VP8Scan[n], ref + VP8Scan[n], tmp[n]);
  }
  VP8FTransformWHT(tmp[0], dc_tmp);
  nz |= VP8EncQuantizeBlock(dc_tmp, rd->y_dc_levels, 0, &dqm->y2_) << 24;

  if (DO_TRELLIS_I16 && it->do_trellis_) {
    int x, y;
    VP8IteratorNzToBytes(it);
    for (y = 0, n = 0; y < 4; ++y) {
      for (x = 0; x < 4; ++x, ++n) {
        const int ctx = it->top_nz_[x] + it->left_nz_[y];
        const int non_zero =
           TrellisQuantizeBlock(it, tmp[n], rd->y_ac_levels[n], ctx, 0,
                                &dqm->y1_, dqm->lambda_trellis_i16_);
        it->top_nz_[x] = it->left_nz_[y] = non_zero;
        nz |= non_zero << n;
      }
    }
  } else {
    for (n = 0; n < 16; ++n) {
      nz |= VP8EncQuantizeBlock(tmp[n], rd->y_ac_levels[n], 1, &dqm->y1_) << n;
    }
  }


  VP8ITransformWHT(dc_tmp, tmp[0]);
  for (n = 0; n < 16; n += 2) {
    VP8ITransform(ref + VP8Scan[n], tmp[n], yuv_out + VP8Scan[n], 1);
  }

  return nz;
}
