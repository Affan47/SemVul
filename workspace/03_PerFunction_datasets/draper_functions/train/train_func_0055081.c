SendURI(const char *u,const char *home)
{
   if(u[0]=='/' && u[1]=='~')
      u++;
   else if(!strncasecmp(u,"/%2F",4))
   {
      Send("/");
      u+=4;
   }
   else if(home && strcmp(home,"/"))
      Send(home);
   SendEncoded(u);
}
