do_join_0(struct Client *client_p, struct Client *source_p)
{
  struct Channel *chptr = NULL;
  dlink_node *ptr = NULL, *ptr_next = NULL;

  if (source_p->channel.head && MyConnect(source_p) && !IsOper(source_p))
    check_spambot_warning(source_p, NULL);

  DLINK_FOREACH_SAFE(ptr, ptr_next, source_p->channel.head)
  {
    chptr = ((struct Membership *)ptr->data)->chptr;

    sendto_server(client_p, chptr, CAP_TS6, NOCAPS,
                  ":%s PART %s", ID(source_p), chptr->chname);
    sendto_server(client_p, chptr, NOCAPS, CAP_TS6,
                  ":%s PART %s", source_p->name, chptr->chname);
    if (!(chptr->mode.mode & MODE_AUDITORIUM))
    {
      sendto_channel_local(ALL_MEMBERS, 0, chptr, ":%s!%s@%s PART %s",
                         source_p->name, source_p->username,
                         source_p->host, chptr->chname);
    }
    else
    {
      sendto_channel_local(CHFL_CHANOP, 0, chptr, ":%s!%s@%s PART %s",
                         source_p->name, source_p->username,
                         source_p->host, chptr->chname);
      sendto_channel_local(CHFL_HALFOP, 0, chptr, ":%s!%s@%s PART %s",
                         source_p->name, source_p->username,
                         source_p->host, chptr->chname);
      sendto_channel_local(CHFL_VOICE, 0, chptr, ":%s!%s@%s PART %s",
                         source_p->name, source_p->username,
                         source_p->host, chptr->chname);
    }

    remove_user_from_channel(ptr->data);
  }
}
