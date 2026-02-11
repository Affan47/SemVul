multigram_add(DFA_INFO *dfa, WORD_INFO *winfo, char *name, PROCESS_LM *lm)
{
  MULTIGRAM *new;


  new = (MULTIGRAM *)mymalloc(sizeof(MULTIGRAM));
  if (name != NULL) {
    strncpy(new->name, name, MAXGRAMNAMELEN);
  } else {
    strncpy(new->name, "(no name)", MAXGRAMNAMELEN);
  }

  new->id = lm->gram_maxid;
  new->dfa = dfa;
  new->winfo = winfo;

  new->hook = MULTIGRAM_DEFAULT | MULTIGRAM_ACTIVATE;
  new->newbie = TRUE;
  new->active = FALSE;


  new->next = lm->grammars;
  lm->grammars = new;

  jlog("STAT: Gram #%d %s registered\n", new->id, new->name);
  lm->gram_maxid++;

  return new->id;
}
