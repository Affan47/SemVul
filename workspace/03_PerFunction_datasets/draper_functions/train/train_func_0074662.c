multigram_load_all_gramlist(PROCESS_LM *lm)
{
  GRAMLIST *g;
  GRAMLIST *groot;
  boolean ok_p;

  switch(lm->config->lmvar) {
  case LM_DFA_GRAMMAR: groot = lm->config->gramlist_root; break;
  case LM_DFA_WORD:    groot = lm->config->wordlist_root; break;
  }

  ok_p = TRUE;
  for(g = groot; g; g = g->next) {
    if (multigram_read_file_and_add(g->dfafile, g->dictfile, lm) == FALSE) {
      ok_p = FALSE;
    }
  }
  return(ok_p);
}
