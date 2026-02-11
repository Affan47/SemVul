listmem_count_from_abe(AdrBk_Entry *abe)
{
    char **p;

    if(abe->tag != List)
      return 0;

    for(p = abe->addr.list; p != NULL && *p != NULL; p++)
      ;

    return((adrbk_cntr_t)(p - abe->addr.list));
}
