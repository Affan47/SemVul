repeat_while(void)
{
  struct macro_head *h;
  yy_size_t macro_src_size = 0;
  char *macro_src;

  h = state.src->h;


  macro_src = make_macro_buffer(h);
  macro_src_size = strlen(macro_src) + 2;

  state.src->line_number = h->line_number + 1;
  state.src->loop_number++;
  state.src->lst.m = h->body;

  yy_delete_buffer(YY_CURRENT_BUFFER);
  yy_scan_buffer(macro_src,macro_src_size);

}
