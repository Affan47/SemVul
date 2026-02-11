cupsArrayDelete(cups_array_t *a)
{


  if (!a)
    return;


  if (a->freefunc)
  {
    int		i;
    void	**e;

    for (i = a->num_elements, e = a->elements; i > 0; i --, e ++)
      (a->freefunc)(*e, a->data);
  }


  if (a->alloc_elements)
    free(a->elements);

  if (a->hashsize)
    free(a->hash);

  free(a);
}
