Write(const void *buf,int size)
{
   if(mode!=STORE)
      return(0);

   Resume();
   Do();
   if(Error())
      return(error_code);

   if(state!=FILE_SEND || rate_limit==0)
      return DO_AGAIN;

   {
      int allowed=rate_limit->BytesAllowedToPut();
      if(allowed==0)
	 return DO_AGAIN;
      if(size+send_buf->Size()>allowed)
	 size=allowed-send_buf->Size();
   }
   if(size+send_buf->Size()>0x4000)
      size=0x4000-send_buf->Size();
   if(pos+size>entity_size)
   {
      size=entity_size-pos;

      if(size==0)
	 return STORE_FAILED;
   }
   if(size<=0)
      return 0;
   send_buf->Put((char*)buf,size);
   TrySuccess();
   rate_limit->BytesPut(size);
   pos+=size;
   real_pos+=size;
   return(size);
}
