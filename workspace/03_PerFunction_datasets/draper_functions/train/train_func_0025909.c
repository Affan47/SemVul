_lf_pinbox_real_free(LF_PINS *pins)
{
  int npins;
  void *list;
  void **addr= NULL;
  void *first= NULL, *last= NULL;
  LF_PINBOX *pinbox= pins->pinbox;

  npins= pinbox->pins_in_array+1;

#ifdef HAVE_ALLOCA
  if (pins->stack_ends_here != NULL)
  {
    int alloca_size= sizeof(void *)*LF_PINBOX_PINS*npins;

    if (available_stack_size(&pinbox, *pins->stack_ends_here) > alloca_size)
    {
      struct st_harvester hv;
      addr= (void **) alloca(alloca_size);
      hv.granary= addr;
      hv.npins= npins;

      _lf_dynarray_iterate(&pinbox->pinarray,
                           (lf_dynarray_func)harvest_pins, &hv);

      npins= hv.granary-addr;

      if (npins)
        qsort(addr, npins, sizeof(void *), (qsort_cmp)ptr_cmp);
    }
  }
#endif

  list= pins->purgatory;
  pins->purgatory= 0;
  pins->purgatory_count= 0;
  while (list)
  {
    void *cur= list;
    list= *(void **)((char *)cur+pinbox->free_ptr_offset);
    if (npins)
    {
      if (addr)
      {
        void **a, **b, **c;
        for (a= addr, b= addr+npins-1, c= a+(b-a)/2; (b-a) > 1; c= a+(b-a)/2)
          if (cur == *c)
            a= b= c;
          else if (cur > *c)
            a= c;
          else
            b= c;
        if (cur == *a || cur == *b)
          goto found;
      }
      else
      {
        if (_lf_dynarray_iterate(&pinbox->pinarray,
                                 (lf_dynarray_func)match_pins, cur))
          goto found;
      }
    }

    if (last)
      last= next_node(pinbox, last)= (uchar *)cur;
    else
      first= last= (uchar *)cur;
    continue;
found:

    add_to_purgatory(pins, cur);
  }
  if (last)
    pinbox->free_func(first, last, pinbox->free_func_arg);
}
