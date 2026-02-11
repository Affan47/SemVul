VP8EncFinishAlpha(VP8Encoder* const enc) {
  if (enc->has_alpha_) {
    if (enc->thread_level_ > 0) {
      WebPWorker* const worker = &enc->alpha_worker_;
      if (!WebPWorkerSync(worker)) return 0;
    }
  }
  return WebPReportProgress(enc->pic_, enc->percent_ + 20, &enc->percent_);
}
