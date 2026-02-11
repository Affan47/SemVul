formatFontString(const char *fontStr_)
{
  static char buf[64];
  const char *fontStr=extractFontString(fontStr_);

  *buf='\0';
  if (fontStr!=0)
   {
     int i;
     for (i=0;i<strlen(fontStr)&&i<64;i++)
      {
	buf[i]=tolower(fontStr_[i]);
      }
     buf[i]='\0';
   }
  return strlen(buf)!=0?buf:0;
}
