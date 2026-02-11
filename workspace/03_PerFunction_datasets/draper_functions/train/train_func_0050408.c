cap_ls(struct Client *sptr, const char *caplist)
{
  if (IsUnknown(sptr))
    sptr->localClient->registration |= REG_NEED_CAP;

  return send_caplist(sptr, 0, 0, "LS");
}
