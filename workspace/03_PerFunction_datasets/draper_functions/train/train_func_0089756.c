multigram_get_id_by_name(PROCESS_LM *lm, char *gramname)
{
  MULTIGRAM *m;

  for(m=lm->grammars;m;m=m->next) {
    if (strmatch(m->name, gramname)) break;
  }
  if (!m) {
    jlog("ERROR: multigram: cannot find grammar \"%s\"\n", gramname);
    return -1;
  }
  return m->id;
}
