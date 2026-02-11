SetSocketBuffer(int sock,int socket_buffer)
{
   if(socket_buffer==0)
      return;
   if(-1==setsockopt(sock,SOL_SOCKET,SO_SNDBUF,(char*)&socket_buffer,sizeof(socket_buffer)))
      ProtoLog::LogError(1,"setsockopt(SO_SNDBUF,%d): %s",socket_buffer,strerror(errno));
   if(-1==setsockopt(sock,SOL_SOCKET,SO_RCVBUF,(char*)&socket_buffer,sizeof(socket_buffer)))
      ProtoLog::LogError(1,"setsockopt(SO_RCVBUF,%d): %s",socket_buffer,strerror(errno));
}
