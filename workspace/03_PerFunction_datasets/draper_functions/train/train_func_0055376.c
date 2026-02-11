memrchr(const char *buf,char c,size_t len)
{
   buf+=len;
   while(len-->0)
      if(*--buf==c)
	 return buf;
   return 0;
}
