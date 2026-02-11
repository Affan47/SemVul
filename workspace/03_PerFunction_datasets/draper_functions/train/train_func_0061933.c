AddPeer(const xstring& addr,int port) const
{
   sockaddr_u a;
#if INET6
   if(addr.instr(':')>=0) {
      a.sa.sa_family=AF_INET6;
      if(inet_pton(AF_INET6,addr,&a.in6.sin6_addr)<=0)
	 return false;
   } else
#endif
   {
      a.sa.sa_family=AF_INET;
      if(!inet_aton(addr,&a.in.sin_addr))
	 return false;
   }
   a.set_port(port);
   Enter(parent);
   parent->AddPeer(new TorrentPeer(parent,&a,tracker_no));
   Leave(parent);
   return true;
}
