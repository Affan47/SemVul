consolidate(Fpa_chunk f, Fpa_list head)
{
  if (f->next && f->n + f->next->n <= f->size) {
    Fpa_chunk f2 = f->next;
    int i;
    for (i = 0; i < f->n; i++)
      f2->d[f->size - (f2->n + i + 1)] = f->d[f->size - (i+1)];
    f2->n = f->n + f2->n;
    free_fpa_chunk(f);
    head->num_chunks--;
    return f2;
  }
  else
    return f;
}
