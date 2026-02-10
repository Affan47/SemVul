expr_free_freers()
{
  struct expr_parse_free *f, *next=NULL;
  for (f=freers; f; f=next) {
    next = f->next;
    free(f->dat);
    free(f);
  }
  freers = NULL;
}
