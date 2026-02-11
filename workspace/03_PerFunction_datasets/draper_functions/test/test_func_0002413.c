del_note_ignore(struct userrec *u, char *mask)
{
  struct user_entry *ue;
  struct xtra_key *xk;
  char **ignores, *buf = NULL;
  int ignoresn, i, size = 0, foundit = 0;

  ignoresn = get_note_ignores(u, &ignores);
  if (!ignoresn)
    return 0;

  buf = user_malloc(1);
  buf[0] = 0;
  for (i = 0; i < ignoresn; i++) {
    if (strcmp(ignores[i], mask)) {
      size += strlen(ignores[i]);
      if (buf[0])
        size++;
      buf = user_realloc(buf, size + 1);
      if (buf[0])
        strcat(buf, " ");
      strcat(buf, ignores[i]);
    } else
      foundit = 1;
  }
  nfree(ignores[0]);
  nfree(ignores);

  if (!foundit) {
    nfree(buf);
    return 0;
  }
  ue = find_user_entry(&USERENTRY_XTRA, u);


  xk = user_malloc(sizeof(struct xtra_key));
  xk->key = user_malloc(strlen(NOTES_IGNKEY) + 1);
  xk->next = 0;

  if (!buf[0]) {
    nfree(buf);
    strcpy(xk->key, NOTES_IGNKEY);
    xk->data = 0;
  } else {
    xk->data = buf;
    strcpy(xk->key, NOTES_IGNKEY);
  }
  xtra_set(u, ue, xk);
  return 1;
}
