m_trace(struct Client* cptr, struct Client* sptr, int parc, char* parv[])
{
  if (feature_bool(FEAT_HIS_TRACE))
    return send_reply(cptr, ERR_NOPRIVILEGES);
  do_trace(cptr, sptr, parc, parv);
  return 0;
}
