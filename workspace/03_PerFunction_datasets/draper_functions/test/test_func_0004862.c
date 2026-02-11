fill_from_channel (MsgChannel *c)
{
  Msg::fill_from_channel (c);
  *c >> port;
  *c >> max_kids;
  c->read_environments( envs );
  *c >> nodename;
  *c >> host_platform;
  uint32_t net_chroot_possible = 0;
  *c >> net_chroot_possible;
  chroot_possible = net_chroot_possible != 0;
  uint32_t net_noremote = 0;
  if (IS_PROTOCOL_26( c )) *c >> net_noremote;
  noremote = (net_noremote != 0);
}
