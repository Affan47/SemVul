chain_append()
{
  if ( chain_ptr != chain && (chain_ptr -1)->end == current_position)
    (chain_ptr -1)->end= next_position;
  else
  {

    if ((off_t)(chain_ptr - chain) == (chain_size -1))
    {
      my_off_t location= chain_ptr - chain;
      chain_size += DEFAULT_CHAIN_LENGTH;
      if (chain_alloced)
      {

        if ((chain= (tina_set *) my_realloc((uchar*)chain,
                                            chain_size, MYF(MY_WME))) == NULL)
          return -1;
      }
      else
      {
        tina_set *ptr= (tina_set *) my_malloc(chain_size * sizeof(tina_set),
                                              MYF(MY_WME));
        memcpy(ptr, chain, DEFAULT_CHAIN_LENGTH * sizeof(tina_set));
        chain= ptr;
        chain_alloced++;
      }
      chain_ptr= chain + location;
    }
    chain_ptr->begin= current_position;
    chain_ptr->end= next_position;
    chain_ptr++;
  }

  return 0;
}
