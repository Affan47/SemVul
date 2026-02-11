ISNSCommUpdate (struct in_addr  *server_addr)
{
   if (server_sock.sin_addr.s_addr != server_addr->s_addr)
      server_sock.sin_addr.s_addr = server_addr->s_addr;
}
