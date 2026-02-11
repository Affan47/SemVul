msg_channel_flags(int p_or_n, const char *command, struct Client *client_p,
                  struct Client *source_p, struct Channel *chptr,
                  int flags, char *text)
{
  int type;
  char c;

  if (flags & CHFL_VOICE)
  {
    type = CHFL_VOICE|CHFL_HALFOP|CHFL_CHANOP;
    c = '+';
  }
#ifdef HALFOPS
  else if (flags & CHFL_HALFOP)
  {
    type = CHFL_HALFOP|CHFL_CHANOP;
    c = '%';
   }
#endif
  else
  {
    type = CHFL_CHANOP;
    c = '@';
  }

  if (MyClient(source_p))
  {

    if (p_or_n != NOTICE)
      source_p->localClient->last = CurrentTime;

    sendto_channel_local_butone(source_p, type, chptr, ":%s!%s@%s %s %c%s :%s",
                                source_p->name, source_p->username,
                                source_p->host, command, c, chptr->chname, text);
  }
  else
  {


    sendto_channel_local(type, YES, chptr, ":%s!%s@%s %s %c%s :%s",
                         source_p->name, source_p->username,
                         source_p->host, command, c, chptr->chname, text);
  }

  if (chptr->chname[0] != '#')
    return;

  sendto_channel_remote(source_p, client_p, type, CAP_CHW, CAP_TS6, chptr,
                ":%s %s %c%s :%s", source_p->name, command, c, chptr->chname, text);
  sendto_channel_remote(source_p, client_p, type, CAP_CHW|CAP_TS6, NOCAPS, chptr,
                ":%s %s %c%s :%s", ID(source_p), command, c, chptr->chname, text);

}
