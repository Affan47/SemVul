caml_output_value_to_malloc(value v, value flags,
                                             char ** buf,
                                             intnat * len)
{
  intnat len_res;
  char * res;
  struct output_block * blk;

  init_extern_output();
  len_res = extern_value(v, flags);
  res = malloc(len_res);
  if (res == NULL) extern_out_of_memory();
  *buf = res;
  *len = len_res;
  for (blk = extern_output_first; blk != NULL; blk = blk->next) {
    int n = blk->end - blk->data;
    memmove(res, blk->data, n);
    res += n;
  }
  free_extern_output();
}
