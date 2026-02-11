Do()
{
   int m=STALL;
   if(Done() || Error())
      return m;

   if(verify)
   {
      if(verify->Error())
	 SetError(verify->ErrorText());
      if(verify->Done())
      {
	 if(suggested_filename && stream && stream->full_name && auto_rename)
	 {
	    const char *new_name=dir_file(dirname(stream->full_name),suggested_filename);
	    struct stat st;
	    if(lstat(new_name,&st)==-1 && errno==ENOENT) {
	       debug((5,"copy: renaming `%s' to `%s'\n",stream->full_name.get(),suggested_filename.get()));
	       if(rename(stream->full_name,new_name)==-1)
		  debug((3,"rename(%s, %s): %s\n",stream->full_name.get(),new_name,strerror(errno)));
	    }
	 }
	 done=true;
	 m=MOVED;
      }
      return m;
   }

   bool check_min_size=true;
#ifndef NATIVE_CRLF
   if(ascii)
      check_min_size=false;
#endif
   switch(mode)
   {
   case PUT:
      if(Size()==0)
      {
	 if(eof)
	 {
	    getfd();
	    if(!date_set && date!=NO_DATE && do_set_date)
	    {
	       if(date==NO_DATE_YET)
		  return m;
	       stream->setmtime(date);
	       date_set=true;
	       m=MOVED;
	    }
	    if(stream && my_stream && !stream->Done())
	       return m;
	    if(!verify && do_verify)
	       verify=new FileVerificator(stream);
	    else
	       done=true;
	    return MOVED;
	 }
	 if(seek_pos==0)
	    return m;
      }
      if(!write_allowed)
	 return m;
      if(getfd()==-1)
	 return m;
      while(Size()>0)
      {
	 if(check_min_size && !eof && Size()<PUT_LL_MIN
	 && put_ll_timer && !put_ll_timer->Stopped())
	    break;
	 int res=Put_LL(buffer+buffer_ptr,Size());
	 if(res>0)
	 {
	    buffer_ptr+=res;
	    m=MOVED;
	 }
	 if(res<0)
	    return MOVED;
	 if(res==0)
	    break;
      }
      break;

   case GET:
      if(eof)
	 return m;
      while(Size()<GET_BUFSIZE)
      {
	 int res=Get_LL(GET_BUFSIZE);
	 if(res>0)
	 {
	    EmbraceNewData(res);
	    SaveMaxCheck(0);
	    m=MOVED;
	 }
	 if(res<0)
	    return MOVED;
	 if(eof)
	    return MOVED;
	 if(res==0)
	    break;
      }
      break;
   }
   return m;
}
