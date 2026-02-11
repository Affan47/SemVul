multigram_free_all(MULTIGRAM *root)
{
  MULTIGRAM *m, *mtmp;

  m = root;
  while(m) {
    mtmp = m->next;
    if (m->dfa) dfa_info_free(m->dfa);
    word_info_free(m->winfo);
    free(m);
    m = mtmp;
  }
}
