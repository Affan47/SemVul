do_who_on_auditorium_channel(struct Client *source_p, struct Channel *chptr,
                  const char *chname, int member)
{
  dlink_node *ptr = NULL, *ptr_next = NULL;
  struct Client *target_p;
  struct Membership *ms, *source_ms;

  DLINK_FOREACH_SAFE(ptr, ptr_next, chptr->members.head)
  {
    ms = ptr->data;
    target_p = ms->client_p;

    if (member)
    {
      source_ms = find_channel_link(source_p, chptr);
      if (IsOper(source_p) || ((ms->flags & (CHFL_CHANOP | CHFL_HALFOP | CHFL_VOICE)) || (source_ms->flags & (CHFL_CHANOP | CHFL_HALFOP | CHFL_VOICE))))
      {
        do_who(source_p, target_p, chname, get_member_status(ms, !!HasCap(source_p, CAP_MULTI_PREFIX)));
      }
    }
    else if (IsOper(source_p) || (!IsInvisible(target_p) && (ms->flags & (CHFL_CHANOP | CHFL_HALFOP | CHFL_VOICE))))
    {
      do_who(source_p, target_p, chname, get_member_status(ms, !!HasCap(source_p, CAP_MULTI_PREFIX)));
    }
  }
}
