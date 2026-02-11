Put_LL(const char *buf,int len)
{
   off_t io_at=pos;
   if(GetRealPos()!=io_at)
      return 0;

   if(len==0 && eof)
      return 0;

   if(o->Full())
      return 0;

   o->Put(buf,len);

   seek_pos+=len;
   return len;
}
