RecordTokens(VP8EncIterator* const it, const VP8ModeScore* const rd,
                         VP8TBuffer* const tokens) {
  int x, y, ch;
  VP8Residual res;
  VP8Encoder* const enc = it->enc_;

  VP8IteratorNzToBytes(it);
  if (it->mb_->type_ == 1) {
    const int ctx = it->top_nz_[8] + it->left_nz_[8];
    InitResidual(0, 1, enc, &res);
    SetResidualCoeffs(rd->y_dc_levels, &res);
    it->top_nz_[8] = it->left_nz_[8] =
        VP8RecordCoeffTokens(ctx, 1,
                             res.first, res.last, res.coeffs, tokens);
    RecordCoeffs(ctx, &res);
    InitResidual(1, 0, enc, &res);
  } else {
    InitResidual(0, 3, enc, &res);
  }


  for (y = 0; y < 4; ++y) {
    for (x = 0; x < 4; ++x) {
      const int ctx = it->top_nz_[x] + it->left_nz_[y];
      SetResidualCoeffs(rd->y_ac_levels[x + y * 4], &res);
      it->top_nz_[x] = it->left_nz_[y] =
          VP8RecordCoeffTokens(ctx, res.coeff_type,
                               res.first, res.last, res.coeffs, tokens);
      RecordCoeffs(ctx, &res);
    }
  }


  InitResidual(0, 2, enc, &res);
  for (ch = 0; ch <= 2; ch += 2) {
    for (y = 0; y < 2; ++y) {
      for (x = 0; x < 2; ++x) {
        const int ctx = it->top_nz_[4 + ch + x] + it->left_nz_[4 + ch + y];
        SetResidualCoeffs(rd->uv_levels[ch * 2 + x + y * 2], &res);
        it->top_nz_[4 + ch + x] = it->left_nz_[4 + ch + y] =
            VP8RecordCoeffTokens(ctx, 2,
                                 res.first, res.last, res.coeffs, tokens);
        RecordCoeffs(ctx, &res);
      }
    }
  }
  VP8IteratorBytesToNz(it);
}
