ra_build_free_all (df)
     struct df *df;
{
  unsigned int i;

  free_bb_info ();
  free (copy_cache);
  copy_cache = NULL;
  for (i = 0; i < df->def_id + df->use_id; i++)
    {
      struct tagged_conflict *cl;
      for (cl = web_parts[i].sub_conflicts; cl; cl = cl->next)
	{
	  if (cl->conflicts)
	    BITMAP_XFREE (cl->conflicts);
	}
      web_parts[i].sub_conflicts = NULL;
    }
  sbitmap_free (live_over_abnormal);
  free (web_parts);
  web_parts = NULL;
  if (last_check_uses)
    sbitmap_free (last_check_uses);
  last_check_uses = NULL;
  free (def2web);
  use2web = NULL;
  def2web = NULL;
}
