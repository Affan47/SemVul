fragment_list_buf_init (struct fragment_list *list, const struct frame *frame)
{
  int i;
  for (i = 0; i < N_FRAG_BUF; ++i)
    list->fragments[i].buf = alloc_buf (BUF_SIZE (frame));
}
