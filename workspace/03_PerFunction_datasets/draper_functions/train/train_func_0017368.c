read(char *buf,int size)
{
   if(error)
      return ERROR;
   int res=do_handshake();
   if(res!=DONE)
      return res;
   errno=0;
   res=gnutls_record_recv(session,buf,size);
   if(res<0)
   {
      if(res==GNUTLS_E_AGAIN || res==GNUTLS_E_INTERRUPTED)
	 return RETRY;
      else if(res==GNUTLS_E_UNEXPECTED_PACKET_LENGTH)
      {
	 Log::global->Format(7,"gnutls_record_recv: %s; assuming EOF\n",gnutls_strerror(res));
	 return 0;
      }
      else
      {
	 fatal=check_fatal(res);
	 set_error("gnutls_record_recv",gnutls_strerror(res));
	 return ERROR;
      }
   }
   return res;
}
