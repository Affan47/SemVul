read_logpoint(void)
{
  unsigned char buffer[SBP_RECORD_LEN];

  if (gbfread(buffer, sizeof(buffer), 1, file_handle) == 1) {
    return navilink_decode_logpoint(buffer);
  }

  return NULL;
}
