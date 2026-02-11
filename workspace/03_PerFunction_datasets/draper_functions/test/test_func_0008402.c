diff2_rgba (guint8 *ip)
{
  return ip[0] != ip[4] || ip[1] != ip[5] || ip[2] != ip[6] || ip[3] != ip[7];
}
