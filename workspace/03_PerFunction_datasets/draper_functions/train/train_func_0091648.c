decomp_block(struct ASPK *stream, uint32_t size, uint8_t *stuff, uint8_t *output) {
  memset(stream->decarray3,0,sizeof(stream->decarray3));
  memset(stream->decarray4,0,sizeof(stream->decarray4));
  memset(stream->decrypt_dict, 0, 757);
  stream->bitpos = 0x20;
  if (!build_decrypt_dictionaries(stream)) return 0;
  return decrypt(stream, stuff, size, output);
}
