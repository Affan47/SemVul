intern_resolve_code_pointer(unsigned char digest[16],
                                          asize_t offset)
{
  int i;
  for (i = caml_code_fragments_table.size - 1; i >= 0; i--) {
    struct code_fragment * cf = caml_code_fragments_table.contents[i];
    if (! cf->digest_computed) {
      caml_md5_block(cf->digest, cf->code_start, cf->code_end - cf->code_start);
      cf->digest_computed = 1;
    }
    if (memcmp(digest, cf->digest, 16) == 0) {
      if (cf->code_start + offset < cf->code_end)
        return cf->code_start + offset;
      else
        return NULL;
    }
  }
  return NULL;
}
