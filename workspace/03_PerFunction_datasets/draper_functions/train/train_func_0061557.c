cleanup_lex_after_parse_error(THD *thd)
{


  if (thd->lex->sphead)
  {
    thd->lex->sphead->restore_thd_mem_root(thd);
    delete thd->lex->sphead;
    thd->lex->sphead= NULL;
  }
}
