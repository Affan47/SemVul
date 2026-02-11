Write(int l,const char *s)
{
   if(!WillOutput(l))
      return;
   DoWrite(s);
}
