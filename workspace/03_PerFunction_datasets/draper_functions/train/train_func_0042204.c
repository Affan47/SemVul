print_cluster (FILE *file, bb_cluster c)
{
  if (c == NULL)
    return;
  bitmap_print (file, c->bbs, "bbs:", "\n");
  bitmap_print (file, c->preds, "preds:", "\n");
}
