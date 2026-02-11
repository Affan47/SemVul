instr(char c) const
{
   char *pos=(char*)memchr(buf,c,len);
   if(!pos)
      return -1;
   return pos-buf;
}
