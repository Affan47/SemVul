append_url_encoded(const char *s,int len,const char *unsafe)
{
   if(!s)
      return *this;
   add_space(len+len/4);
   while(len-->0)
   {
      char c=*s++;
      if (need_quote(c))
	 appendf("%%%02X",(unsigned char)c);
      else
	 append(c);
   }
   return *this;
}
