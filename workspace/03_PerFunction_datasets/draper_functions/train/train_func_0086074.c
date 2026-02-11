PickBestIntra16(VP8EncIterator* const it, VP8ModeScore* const rd) {
  const VP8Encoder* const enc = it->enc_;
  const VP8SegmentInfo* const dqm = &enc->dqm_[it->mb_->segment_];
  const int lambda = dqm->lambda_i16_;
  const int tlambda = dqm->tlambda_;
  const uint8_t* const src = it->yuv_in_ + Y_OFF;
  VP8ModeScore rd16;
  int mode;

  rd->mode_i16 = -1;
  for (mode = 0; mode < NUM_PRED_MODES; ++mode) {
    uint8_t* const tmp_dst = it->yuv_out2_ + Y_OFF;
    int nz;


    nz = ReconstructIntra16(it, &rd16, tmp_dst, mode);


    rd16.D = VP8SSE16x16(src, tmp_dst);
    rd16.SD = tlambda ? MULT_8B(tlambda, VP8TDisto16x16(src, tmp_dst, kWeightY))
            : 0;
    rd16.R = VP8GetCostLuma16(it, &rd16);
    rd16.R += VP8FixedCostsI16[mode];


    SetRDScore(lambda, &rd16);
    if (mode == 0 || rd16.score < rd->score) {
      CopyScore(rd, &rd16);
      rd->mode_i16 = mode;
      rd->nz = nz;
      memcpy(rd->y_ac_levels, rd16.y_ac_levels, sizeof(rd16.y_ac_levels));
      memcpy(rd->y_dc_levels, rd16.y_dc_levels, sizeof(rd16.y_dc_levels));
      SwapOut(it);
    }
  }
  SetRDScore(dqm->lambda_mode_, rd);
  VP8SetIntra16Mode(it, rd->mode_i16);
}
