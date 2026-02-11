csv_free(struct csv_parser *p)
{

  if (p == NULL)
    return;

  if (p->entry_buf)
    p->free_func(p->entry_buf);

  p->entry_buf = NULL;
  p->entry_size = 0;

  return;
}
