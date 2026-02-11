add_message(int lidx, char *ltext)
{
  lang_tab *l = langtab[lidx & 63];

  while (l) {
    if (l->idx && (l->idx == lidx)) {
      nfree(l->text);
      l->text = nmalloc(strlen(ltext) + 1);
      strcpy(l->text, ltext);
      return 1;
    }
    if (!l->next)
      break;
    l = l->next;
  }
  if (l) {
    l->next = nmalloc(sizeof(lang_tab));
    l = l->next;
  } else
    l = langtab[lidx & 63] = nmalloc(sizeof(lang_tab));
  l->idx = lidx;
  l->text = nmalloc(strlen(ltext) + 1);
  strcpy(l->text, ltext);
  l->next = 0;
  return 0;
}
