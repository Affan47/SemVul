buffer_get_bignum(Buffer *buffer, BIGNUM *value)
{
  sint32_t bytes;
  uint8_t *bin;


  bytes = buffer_get_int(buffer);
  if (bytes > 8 * 1024) {
    Display(LOG_LEVEL_1, ELError, "buffer_get_bignum", GOGO_STR_CANT_HANDLE_BN_SIZE, bytes);
    exit(1);
  }
  if( (sint32_t)buffer_len(buffer) < bytes) {
    Display(LOG_LEVEL_1, ELError, "buffer_get_bignum", GOGO_STR_INPUT_BUF_TOO_SMALL);
    exit(1);
  }
  bin = buffer_ptr(buffer);
  BN_bin2bn(bin, bytes, value);
  buffer_consume(buffer, bytes);
}
