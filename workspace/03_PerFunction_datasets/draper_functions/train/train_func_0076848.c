snappy_compress(const char* input,
                              size_t input_length,
                              char* compressed,
                              size_t *compressed_length) {
  if (*compressed_length < snappy_max_compressed_length(input_length)) {
    return SNAPPY_BUFFER_TOO_SMALL;
  }
  snappy::RawCompress(input, input_length, compressed, compressed_length);
  return SNAPPY_OK;
}
