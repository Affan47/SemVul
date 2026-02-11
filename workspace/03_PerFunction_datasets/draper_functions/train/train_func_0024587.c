IsInvited(struct Client* cptr, const void* chptr)
{
  struct SLink *lp;

  for (lp = (cli_user(cptr))->invited; lp; lp = lp->next)
    if (lp->value.chptr == chptr)
      return 1;
  return 0;
}
