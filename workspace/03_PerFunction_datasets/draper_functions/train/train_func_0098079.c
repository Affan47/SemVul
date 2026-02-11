ProcessRawProfile(const char* profile, size_t profile_len,
                             MetadataPayload* const payload) {
  const char* src = profile;
  char* end;
  int expected_length;

  if (profile == NULL || profile_len == 0) return 0;


  if (*src != '\n') {
    fprintf(stderr, "Malformed raw profile, expected '\\n' got '\\x%.2X'\n",
            *src);
    return 0;
  }
  ++src;

  while (*src != '\0' && *src++ != '\n') {}
  expected_length = (int)strtol(src, &end, 10);
  if (*end != '\n') {
    fprintf(stderr, "Malformed raw profile, expected '\\n' got '\\x%.2X'\n",
            *end);
    return 0;
  }
  ++end;


  payload->bytes = HexStringToBytes(end, expected_length);
  if (payload->bytes == NULL) return 0;
  payload->size = expected_length;
  return 1;
}
