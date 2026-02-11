ooH323GetIpPortFromH225TransportAddress(struct OOH323CallData *call,
   H225TransportAddress *h225Address, char *ip, int *port)
{
   if (call->versionIP == 6) {
    if(h225Address->t != T_H225TransportAddress_ip6Address)
    {
      OOTRACEERR3("Error: Unknown H225 address type. (%s, %s)", call->callType,
                   call->callToken);
      return OO_FAILED;
    }
    inet_ntop(AF_INET6, h225Address->u.ip6Address->ip.data, ip, INET6_ADDRSTRLEN);
    *port = h225Address->u.ip6Address->port;
    return OO_OK;
   }
   if(h225Address->t != T_H225TransportAddress_ipAddress)
   {
      OOTRACEERR3("Error: Unknown H225 address type. (%s, %s)", call->callType,
                   call->callToken);
      return OO_FAILED;
   }
   sprintf(ip, "%d.%d.%d.%d",
              h225Address->u.ipAddress->ip.data[0],
              h225Address->u.ipAddress->ip.data[1],
              h225Address->u.ipAddress->ip.data[2],
              h225Address->u.ipAddress->ip.data[3]);
   *port = h225Address->u.ipAddress->port;
   return OO_OK;
}
