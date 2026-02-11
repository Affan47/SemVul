DoConnect(struct addrinfo *Addr,std::string Host,
		      unsigned long TimeOut,int &Fd,pkgAcqMethod *Owner)
{

   char Name[NI_MAXHOST];
   char Service[NI_MAXSERV];

   Name[0] = 0;
   Service[0] = 0;
   getnameinfo(Addr->ai_addr,Addr->ai_addrlen,
	       Name,sizeof(Name),Service,sizeof(Service),
	       NI_NUMERICHOST|NI_NUMERICSERV);
   Owner->Status(_("Connecting to %s (%s)"),Host.c_str(),Name);


   if(bad_addr.find(std::string(Name)) != bad_addr.end())
      return false;


   if (LastHostAddr->ai_next != 0)
   {
      std::stringstream ss;
      ioprintf(ss, _("[IP: %s %s]"),Name,Service);
      Owner->SetIP(ss.str());
   }


   if ((Fd = socket(Addr->ai_family,Addr->ai_socktype,
		    Addr->ai_protocol)) < 0)
      return _error->Errno("socket",_("Could not create a socket for %s (f=%u t=%u p=%u)"),
			   Name,Addr->ai_family,Addr->ai_socktype,Addr->ai_protocol);

   SetNonBlock(Fd,true);
   if (connect(Fd,Addr->ai_addr,Addr->ai_addrlen) < 0 &&
       errno != EINPROGRESS)
      return _error->Errno("connect",_("Cannot initiate the connection "
			   "to %s:%s (%s)."),Host.c_str(),Service,Name);


   if (WaitFd(Fd,true,TimeOut) == false) {
      bad_addr.insert(bad_addr.begin(), std::string(Name));
      Owner->SetFailReason("Timeout");
      return _error->Error(_("Could not connect to %s:%s (%s), "
			   "connection timed out"),Host.c_str(),Service,Name);
   }


   unsigned int Err;
   unsigned int Len = sizeof(Err);
   if (getsockopt(Fd,SOL_SOCKET,SO_ERROR,&Err,&Len) != 0)
      return _error->Errno("getsockopt",_("Failed"));

   if (Err != 0)
   {
      errno = Err;
      if(errno == ECONNREFUSED)
         Owner->SetFailReason("ConnectionRefused");
      else if (errno == ETIMEDOUT)
	 Owner->SetFailReason("ConnectionTimedOut");
      bad_addr.insert(bad_addr.begin(), std::string(Name));
      return _error->Errno("connect",_("Could not connect to %s:%s (%s)."),Host.c_str(),
			   Service,Name);
   }

   return true;
}
