WebPIDecode(const uint8_t* data, size_t data_size,
                          WebPDecoderConfig* config) {
  WebPIDecoder* idec;


  if (data != NULL && data_size > 0 && config != NULL) {
    if (WebPGetFeatures(data, data_size, &config->input) != VP8_STATUS_OK) {
      return NULL;
    }
  }

  idec = WebPINewDecoder(config ? &config->output : NULL);
  if (idec == NULL) {
    return NULL;
  }

  if (config != NULL) {
    idec->params_.options = &config->options;
  }
  return idec;
}
