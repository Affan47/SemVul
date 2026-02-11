Put_LL(const char *buf,int len)
{
   if(len==0)
      return 0;

   int fd=getfd();
   if(fd==-1)
      return 0;

   int skip_cr=0;

#ifndef NATIVE_CRLF
   if(ascii)
   {

      const char *cr=buf;
      for(;;)
      {
	 cr=(const char *)memchr(cr,'\r',len-(cr-buf));
	 if(!cr)
	    break;
	 if(cr-buf<len-1 && cr[1]=='\n')
	 {
	    skip_cr=1;
	    len=cr-buf;
	    break;
	 }
	 if(cr-buf==len-1)
	 {
	    if(eof)
	       break;
	    len--;
	    break;
	 }
	 cr++;
      }
   }
#endif

   if(len==0)
      return skip_cr;

   if(need_seek)
      lseek(fd,seek_base+pos-Size(),SEEK_SET);

   int res=write(fd,buf,len);
   if(res<0)
   {
      if(E_RETRY(errno))
      {
	 Block(fd,POLLOUT);
	 return 0;
      }
      if(errno==EPIPE)
      {
	 broken=true;
	 buffer.truncate(buffer_ptr);
	 eof=true;
	 return -1;
      }
      if(stream->NonFatalError(errno))
      {

	 if(errno==ENOSPC && can_seek)
	 {
	    struct stat st;
	    if(fstat(fd,&st)!=-1)
	    {
	       if(st.st_size<seek_base+pos-Size())
	       {

		  if(buffer_ptr>=seek_base+pos-Size()-buffer_ptr-st.st_size)
		     UnSkip(seek_base+pos-Size()-st.st_size);
		  else
		  {
		     Empty();
		     pos=st.st_size;
		  }
	       }
	    }
	 }
	 return 0;
      }
      stream->MakeErrorText();
      SetError(stream->error_text);
      return -1;
   }
   stream->clear_status();
   if(res==len && skip_cr)
   {
      res+=skip_cr;


      if(write(fd,"\n",1)==1)
	 res+=1;
   }
   if(put_ll_timer)
      put_ll_timer->Reset();
   return res;
}
