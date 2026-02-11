WebPIUpdate(WebPIDecoder* idec,
                          const uint8_t* data, size_t data_size) {
  VP8StatusCode status;
  if (idec == NULL || data == NULL) {
    return VP8_STATUS_INVALID_PARAM;
  }
  status = IDecCheckStatus(idec);
  if (status != VP8_STATUS_SUSPENDED) {
    return status;
  }

  if (!CheckMemBufferMode(&idec->mem_, MEM_MODE_MAP)) {
    return VP8_STATUS_INVALID_PARAM;
  }

  if (!RemapMemBuffer(idec, data, data_size)) {
    return VP8_STATUS_INVALID_PARAM;
  }
  return IDecode(idec);
}
