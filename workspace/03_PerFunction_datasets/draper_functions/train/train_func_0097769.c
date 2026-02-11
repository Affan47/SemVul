read_pk0304_header(const gar_gfile_t *gf, pk0304_header_t *hdr,
                              jmp_buf env) {
  byte_t s[30];
  size_t n;


  n = gar_gfile_read(gf, s, sizeof(s), env);
  if (n < sizeof(s) || memcmp(s, "PK\3\4", 4)) {
    return 0;
  }


  decode_u32_le(&s[0], &hdr->sig);
  decode_u16_le(&s[4], &hdr->need_ver);
  decode_u16_le(&s[6], &hdr->flags);
  decode_u16_le(&s[8], &hdr->comp_method);
  decode_u16_le(&s[10], &hdr->last_mod_time);
  decode_u16_le(&s[12], &hdr->last_mod_date);
  decode_u32_le(&s[14], &hdr->crc32);
  decode_u32_le(&s[18], &hdr->comp_size);
  decode_u32_le(&s[22], &hdr->uncomp_size);
  decode_u16_le(&s[26], &hdr->fname_len);
  decode_u16_le(&s[28], &hdr->extra_len);

  return 1;
}
