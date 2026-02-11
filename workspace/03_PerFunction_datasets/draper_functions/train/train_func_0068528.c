obstcp_advert_base32_parse(const char *input, unsigned length, ...) {
  va_list ap;
  va_start(ap, length);
  uint8_t advert[384];
  const unsigned decoded_length = base32_decode_length(length);

  if (decoded_length > sizeof(advert)) return 0;
  if (!base32_decode(advert, input, length)) return 0;

  const int r = advert_parse(advert, decoded_length, ap);
  va_end(ap);

  return r;
}
