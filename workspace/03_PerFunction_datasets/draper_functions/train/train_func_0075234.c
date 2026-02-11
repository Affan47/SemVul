removefrommemberlist(channel_t *c, const char *nick)
{
  member_t *member;

  updatecontext();

  if (gdata.debug > 2)
    {
      ioutput(CALLTYPE_NORMAL,OUT_S,COLOR_NO_COLOR,
              "removing %s from %s",nick,c->name);
    }


  member = irlist_get_head(&c->members);
  while(member)
    {
      if (!strcasecmp(member->nick,nick))
        {
          irlist_delete(&c->members, member);
          return;
        }
      member = irlist_get_next(member);
    }


  return;
}
