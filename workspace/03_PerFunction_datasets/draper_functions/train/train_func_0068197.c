DoGethostbyname()
{
   if(port_number==0)
   {
      const char *tproto=proto?proto.get():"tcp";
      const char *tport=portname?portname.get():defport.get();

      if(isdigit((unsigned char)tport[0]))
	 port_number=htons(atoi(tport));
      else
      {
	 struct servent *se=getservbyname(tport,tproto);
	 if(se)
	    port_number=se->s_port;
	 else
	 {
	    buf->Put("P");
	    buf->Format(_("no such %s service"),tproto);
	    goto flush;
	 }
      }
   }

   if(service && !portname && !isdigit((unsigned char)hostname[0]))
      LookupSRV_RR();

   if(!use_fork && deleting)
      return;

   LookupOne(hostname);

   if(!use_fork && deleting)
      return;

   if(addr.count()==0)
   {
      buf->Put("E");
      if(error==0)
	 error=_("No address found");
      buf->Put(error);
      goto flush;
   }
   buf->Put("O");
   buf->Put((const char*)addr.get(),addr.count()*addr.get_element_size());
   addr.unset();

flush:
   buf->PutEOF();
   if(use_fork)
   {
      while(buf->Size()>0 && !buf->Error() && !buf->Broken())
	 buf->Roll();
   }
}
