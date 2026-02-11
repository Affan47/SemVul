VP8EncWrite(VP8Encoder* const enc) {
  WebPPicture* const pic = enc->pic_;
  VP8BitWriter* const bw = &enc->bw_;
  const int task_percent = 19;
  const int percent_per_part = task_percent / enc->num_parts_;
  const int final_percent = enc->percent_ + task_percent;
  int ok = 0;
  size_t vp8_size, pad, riff_size;
  int p;


  ok = GeneratePartition0(enc);
  if (!ok) return 0;


  vp8_size = VP8_FRAME_HEADER_SIZE +
             VP8BitWriterSize(bw) +
             3 * (enc->num_parts_ - 1);
  for (p = 0; p < enc->num_parts_; ++p) {
    vp8_size += VP8BitWriterSize(enc->parts_ + p);
  }
  pad = vp8_size & 1;
  vp8_size += pad;


  riff_size = TAG_SIZE + CHUNK_HEADER_SIZE + vp8_size;
  if (IsVP8XNeeded(enc)) {
    riff_size += CHUNK_HEADER_SIZE + VP8X_CHUNK_SIZE;
  }
  if (enc->has_alpha_) {
    const uint32_t padded_alpha_size = enc->alpha_data_size_ +
                                       (enc->alpha_data_size_ & 1);
    riff_size += CHUNK_HEADER_SIZE + padded_alpha_size;
  }

  if (riff_size > 0xfffffffeU) {
    return WebPEncodingSetError(pic, VP8_ENC_ERROR_FILE_TOO_BIG);
  }


  {
    const uint8_t* const part0 = VP8BitWriterBuf(bw);
    const size_t size0 = VP8BitWriterSize(bw);
    ok = ok && PutWebPHeaders(enc, size0, vp8_size, riff_size)
            && pic->writer(part0, size0, pic)
            && EmitPartitionsSize(enc, pic);
    VP8BitWriterWipeOut(bw);
  }


  for (p = 0; p < enc->num_parts_; ++p) {
    const uint8_t* const buf = VP8BitWriterBuf(enc->parts_ + p);
    const size_t size = VP8BitWriterSize(enc->parts_ + p);
    if (size)
      ok = ok && pic->writer(buf, size, pic);
    VP8BitWriterWipeOut(enc->parts_ + p);
    ok = ok && WebPReportProgress(pic, enc->percent_ + percent_per_part,
                                  &enc->percent_);
  }


  if (ok && pad) {
    ok = PutPaddingByte(pic);
  }

  enc->coded_size_ = (int)(CHUNK_HEADER_SIZE + riff_size);
  ok = ok && WebPReportProgress(pic, final_percent, &enc->percent_);
  return ok;
}
