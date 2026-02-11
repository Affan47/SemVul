netio_tcp_recv(netio_inet_desc_t *nid,void *pkt,size_t max_len)
{
   u_long l;

   if (read(nid->fd,&l,sizeof(l)) != sizeof(l))
      return(-1);

   if (ntohl(l) > max_len)
      return(-1);

   return(read(nid->fd,pkt,ntohl(l)));
}
