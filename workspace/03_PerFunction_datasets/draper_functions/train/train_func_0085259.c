send_res_msg(const char *msg, int len, int rcount)
{
  int i;
  int sent = 0;
  int max_queries = IRCD_MIN(irc_nscount, rcount);


  if (max_queries == 0)
    max_queries = 1;

  for (i = 0; i < max_queries; i++)
  {
    if (sendto(ResolverFileDescriptor.fd, msg, len, 0,
        (struct sockaddr*)&(irc_nsaddr_list[i]),
        irc_nsaddr_list[i].ss_len) == len)
      ++sent;
  }

  return sent;
}
