Put_LL(const char *buf,int size)
{
   int res=ssl->write(buf,size);
   if(res<0)
   {
      if(res==ssl->RETRY)
	 return 0;
      else
      {
	 SetError(ssl->error,ssl->fatal);
	 return -1;
      }
   }
   return res;
}
