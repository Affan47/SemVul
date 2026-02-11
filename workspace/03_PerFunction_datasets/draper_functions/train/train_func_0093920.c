extern_find_code(char *addr)
{
  int i;
  for (i = caml_code_fragments_table.size - 1; i >= 0; i--) {
    struct code_fragment * cf = caml_code_fragments_table.contents[i];
    if (! cf->digest_computed) {
      caml_md5_block(cf->digest, cf->code_start, cf->code_end - cf->code_start);
      cf->digest_computed = 1;
    }
    if (cf->code_start <= addr && addr < cf->code_end) return cf;
  }
  return NULL;
}
