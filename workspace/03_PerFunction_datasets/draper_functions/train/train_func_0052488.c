create_new_ivs (struct ivopts_data *data, struct iv_ca *set)
{
  unsigned i;
  struct iv_cand *cand;
  bitmap_iterator bi;

  EXECUTE_IF_SET_IN_BITMAP (set->cands, 0, i, bi)
    {
      cand = iv_cand (data, i);
      create_new_iv (data, cand);
    }

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "\nSelected IV set: \n");
      EXECUTE_IF_SET_IN_BITMAP (set->cands, 0, i, bi)
        {
          cand = iv_cand (data, i);
          dump_cand (dump_file, cand);
        }
      fprintf (dump_file, "\n");
    }
}
