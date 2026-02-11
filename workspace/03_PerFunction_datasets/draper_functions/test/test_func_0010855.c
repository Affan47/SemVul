fttag_def_eval(struct fttag_def *ftd,
  struct fts3rec_v1005 *rec)
{
  struct fttag_def_term *ftdt;
  struct fttag_def_term_actions *ftdta;
  struct fttag_action *fta;


  FT_STAILQ_FOREACH(ftdt, &ftd->terms, chain) {


    if (!ftdt->in_tbl[rec->input])
      continue;


    if (!ftdt->out_tbl[rec->output])
      continue;

    if (ftdt->flags & FT_TAG_DEF_FILTER_EXPORTER)
      if (ftdt->exporter_ip != rec->exaddr)
        continue;


    FT_STAILQ_FOREACH(ftdta, &ftdt->actions, chain) {


      fta = ftdta->action;


      fta->eval(fta, rec);

    }

  }

  return 0;

}
