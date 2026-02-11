sendto_realops_flags(unsigned int flags, int level, const char *pattern, ...)
{
  dlink_node *ptr = NULL;
  char nbuf[IRCD_BUFSIZE];
  va_list args;

  va_start(args, pattern);
  vsnprintf(nbuf, IRCD_BUFSIZE, pattern, args);
  va_end(args);

  DLINK_FOREACH(ptr, oper_list.head)
  {
    struct Client *client_p = ptr->data;
    assert(client_p->umodes & UMODE_OPER);


    if (((level == L_ADMIN) && !IsAdmin(client_p)) ||
	((level == L_OPER) && IsAdmin(client_p)))
      continue;

    if (client_p->umodes & flags)
      sendto_one(client_p, ":%s NOTICE %s :*** Notice -- %s",
                 me.name, client_p->name, nbuf);
  }
}
