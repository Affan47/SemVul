tcl_binds STDVAR
{
  int matching = 0;
  char *g, flg[100], hits[11];
  EGG_CONST char *list[5];
  tcl_bind_list_t *tl, *tl_kind;
  tcl_bind_mask_t *tm;
  tcl_cmd_t *tc;

  BADARGS(1, 2, " ?type/mask?");

  if (argv[1])
    tl_kind = find_bind_table(argv[1]);
  else
    tl_kind = NULL;
  if (!tl_kind && argv[1])
    matching = 1;
  for (tl = tl_kind ? tl_kind : bind_table_list; tl;
       tl = tl_kind ? 0 : tl->next) {
    if (tl->flags & HT_DELETED)
      continue;
    for (tm = tl->first; tm; tm = tm->next) {
      if (tm->flags & TBM_DELETED)
        continue;
      for (tc = tm->first; tc; tc = tc->next) {
        if (tc->attributes & TC_DELETED)
          continue;
        if (matching &&
            !wild_match_per(argv[1], tl->name) &&
            !wild_match_per(argv[1], tm->mask) &&
            !wild_match_per(argv[1], tc->func_name))
          continue;
        build_flags(flg, &(tc->flags), NULL);
        egg_snprintf(hits, sizeof hits, "%i", (int) tc->hits);
        list[0] = tl->name;
        list[1] = flg;
        list[2] = tm->mask;
        list[3] = hits;
        list[4] = tc->func_name;
        g = Tcl_Merge(5, list);
        Tcl_AppendElement(irp, g);
        Tcl_Free((char *) g);
      }
    }
  }
  return TCL_OK;
}
