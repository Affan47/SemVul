SetupMatrices(VP8Encoder* enc) {
  int i;
  const int tlambda_scale =
    (enc->method_ >= 4) ? enc->config_->sns_strength
                        : 0;
  const int num_segments = enc->segment_hdr_.num_segments_;
  for (i = 0; i < num_segments; ++i) {
    VP8SegmentInfo* const m = &enc->dqm_[i];
    const int q = m->quant_;
    int q4, q16, quv;
    m->y1_.q_[0] = kDcTable[clip(q + enc->dq_y1_dc_, 0, 127)];
    m->y1_.q_[1] = kAcTable[clip(q,                  0, 127)];

    m->y2_.q_[0] = kDcTable[ clip(q + enc->dq_y2_dc_, 0, 127)] * 2;
    m->y2_.q_[1] = kAcTable2[clip(q + enc->dq_y2_ac_, 0, 127)];

    m->uv_.q_[0] = kDcTable[clip(q + enc->dq_uv_dc_, 0, 117)];
    m->uv_.q_[1] = kAcTable[clip(q + enc->dq_uv_ac_, 0, 127)];

    q4  = ExpandMatrix(&m->y1_, 0);
    q16 = ExpandMatrix(&m->y2_, 1);
    quv = ExpandMatrix(&m->uv_, 2);


    {
      m->lambda_i4_  = (3 * q4 * q4) >> 7;
      m->lambda_i16_ = (3 * q16 * q16);
      m->lambda_uv_  = (3 * quv * quv) >> 6;
      m->lambda_mode_    = (1 * q4 * q4) >> 7;
      m->lambda_trellis_i4_  = (7 * q4 * q4) >> 3;
      m->lambda_trellis_i16_ = (q16 * q16) >> 2;
      m->lambda_trellis_uv_  = (quv *quv) << 1;
      m->tlambda_            = (tlambda_scale * q4) >> 5;
    }
  }
}
