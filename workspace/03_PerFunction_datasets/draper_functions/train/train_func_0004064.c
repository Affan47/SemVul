cap_clear(struct Client *sptr, const char *caplist)
{
  struct CapSet cleared;
  struct capabilities *cap;
  unsigned int ii;


  memset(&cleared, 0, sizeof(cleared));
  for (ii = 0; ii < CAPAB_LIST_LEN; ++ii) {
    cap = &capab_list[ii];

    if (!HasCap(sptr, cap->cap) || (cap->flags & CAPFL_STICKY))
      continue;
    CapSet(&cleared, cap->cap);
    CapClr(cli_capab(sptr), cap->cap);
    if (!(cap->flags & CAPFL_PROTO))
      CapClr(cli_active(sptr), cap->cap);
  }
  send_caplist(sptr, 0, &cleared, "ACK");

  return 0;
}
