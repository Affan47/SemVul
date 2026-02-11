nxtnet_recv(int sock,struct nxtnet_proto_packet *buf,int cmd) {
  ssize_t size;
  uint32_t packet_sig;
  uint16_t packet_size;


  do size = recv(sock,buf,sizeof(struct nxtnet_proto_packet),MSG_PEEK);
  while (size>0 && size<sizeof(struct nxtnet_proto_packet));

  packet_sig = ntohl(buf->sig);
  packet_size = ntohs(buf->size);


  if (size>0 && packet_sig==NXTNET_PROTO_SIG && (cmd==0 || buf->cmd==cmd) && packet_size<=NXTNET_BUFSIZE) {


    size = 0;
    while (size<packet_size) size += recv(sock,buf+size,packet_size-size,0);


    buf->sig = packet_sig;
    buf->size = packet_size;

    return buf;
  }
  else return NULL;
}
