GetOutputBuffer(const WebPIDecoder* const idec) {
  if (idec == NULL || idec->dec_ == NULL) {
    return NULL;
  }
  if (idec->state_ <= STATE_VP8_PARTS0) {
    return NULL;
  }
  return idec->params_.output;
}
