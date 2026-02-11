SendEncoded(const char *buf)
{
   while(*buf)
   {
      char ch=*buf++;
      if(ch=='%' && isxdigit((unsigned char)buf[0]) && isxdigit((unsigned char)buf[1]))
      {
	 int n=0;
	 if(sscanf(buf,"%2x",&n)==1)
	 {
	    buf+=2;
	    ch=n;

	    send_cmd_buffer.PutRaw(&ch,1);
	    send_cmd_buffer.ResetTranslation();
	    goto next;
	 }
      }
      send_cmd_buffer.Put(&ch,1);
next: if(ch=='\r')
	 send_cmd_buffer.PutRaw("",1);
   }
}
