Do()
{
   if(Done() || Error())
      return STALL;
   int res=0;
   switch(mode)
   {
   case PUT:
      if(Size()==0)
	 return STALL;
      res=Put_LL(buffer+buffer_ptr,Size());
      if(res>0)
      {
	 RateAdd(res);
	 buffer_ptr+=res;
	 event_time=now;
	 return MOVED;
      }
      break;

   case GET:
      if(eof)
	 return STALL;
      res=Get_LL(GET_BUFSIZE);
      if(res>0)
      {
	 EmbraceNewData(res);
	 event_time=now;
	 return MOVED;
      }
      if(eof)
      {
	 event_time=now;
	 return MOVED;
      }
      break;
   }
   if(res<0)
   {
      event_time=now;
      return MOVED;
   }
   return STALL;
}
