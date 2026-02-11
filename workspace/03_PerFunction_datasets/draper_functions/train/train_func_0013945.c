ftchash_sort(struct ftchash *ftch, int offset, int flags)
{
  void *rec;
  u_int64 x;


  if (!ftch->entries)
    return 0;


  if (ftch->sorted_recs)
    free(ftch->sorted_recs);


  if (!(ftch->sorted_recs = (struct ftchash_rec_gen**)
    malloc(sizeof (struct ftchash_rec_gen*)*ftch->entries))) {
    fterr_warn("malloc()");
    return -1;
  }

  ftch->sort_flags = flags;


  ftchash_first(ftch);
  x = 0;
  while ((rec = ftchash_foreach(ftch))) {

    ftch->sorted_recs[x++] = (struct ftchash_rec_gen*)rec;

  }

  sort_offset = offset;

  if (flags & FT_CHASH_SORT_64)
    qsort(ftch->sorted_recs, ftch->entries, sizeof (void*), cmp64);
  else if (flags & FT_CHASH_SORT_40)
    qsort(ftch->sorted_recs, ftch->entries, sizeof (void*), cmp40);
  else if (flags & FT_CHASH_SORT_32)
    qsort(ftch->sorted_recs, ftch->entries, sizeof (void*), cmp32);
  else if (flags & FT_CHASH_SORT_16)
    qsort(ftch->sorted_recs, ftch->entries, sizeof (void*), cmp16);
  else if (flags & FT_CHASH_SORT_8)
    qsort(ftch->sorted_recs, ftch->entries, sizeof (void*), cmp8);
  else if (flags & FT_CHASH_SORT_DOUBLE)
    qsort(ftch->sorted_recs, ftch->entries, sizeof (void*), cmp_double);
  else
    fterr_errx(1, "ftchash_sort(): internal error");

  ftch->sort_flags |= FT_CHASH_SORTED;

  return 0;

}
