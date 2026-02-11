getnotesentry(struct userrec *u)
{
  struct user_entry *ue = find_user_entry(&USERENTRY_XTRA, u);
  struct xtra_key *xk, *nxk = NULL;

  if (!ue)
    return NULL;

  for (xk = ue->u.extra; xk; xk = xk->next)
    if (xk->key && !egg_strcasecmp(xk->key, NOTES_IGNKEY)) {
      nxk = xk;
      break;
    }
  if (!nxk || !nxk->data || !(nxk->data[0]))
    return NULL;
  return nxk;
}
