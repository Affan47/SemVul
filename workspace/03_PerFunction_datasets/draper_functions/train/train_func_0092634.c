mcnet_parser_execute(mcnet_parser_t* parser, mcnet_parser_settings_t* settings, uint8_t* data, size_t data_len) {
  if (data_len < 1) {
    if (settings->on_error != NULL) {
      settings->on_error(parser, MCNET_EAGAIN);
    }

    return MCNET_EAGAIN;
  }

  switch (data[0]) {
    PACKETS

    default: {
      if (settings->on_error != NULL) {
        settings->on_error(parser, MCNET_EINVALID);
      }

      return MCNET_EINVALID;
    }
  }

  return MCNET_EAGAIN;
}
