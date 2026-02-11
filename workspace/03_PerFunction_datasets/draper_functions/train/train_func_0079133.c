argv_iter_init_stream (FILE *fp)
{
  struct argv_iterator *ai = malloc (sizeof *ai);
  if (!ai)
    return NULL;
  ai->fp = fp;
  ai->tok = NULL;
  ai->buf_len = 0;

  ai->item_idx = 0;
  ai->arg_list = NULL;
  return ai;
}
