genlist_clear(struct genlist *pgenlist)
{
  fc_assert_ret(NULL != pgenlist);

  if (0 < pgenlist->nelements) {
    genlist_free_fn_t free_data_func = pgenlist->free_data_func;
    struct genlist_link *plink = pgenlist->head_link, *plink2;

    pgenlist->head_link = NULL;
    pgenlist->tail_link = NULL;

    pgenlist->nelements = 0;

    do {
      plink2 = plink->next;
      free_data_func(plink->dataptr);
      free(plink);
    } while ((plink = plink2) != NULL);
  }
}
