tagtoname(char const tag[],char const *&t)
{
  char const *s;
  for(s=tag;isspace(*s);s++);
  for(t=s;(*t)&&((*t)!='>')&&((*t)!='/')&&!isspace(*t);++t);
  return GUTF8String(s,t-s);
}
