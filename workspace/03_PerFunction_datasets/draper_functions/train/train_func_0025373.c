GetBytesRemaining() const
{
   if(!get)
      return 0;
   if(get->range_limit==FILE_END)
   {
      off_t size=get->GetSize();
      if(size<=0 || size<get->GetRealPos() || !rate_for_eta->Valid())
	 return -1;
      return(size-GetPos());
   }
   return get->range_limit-GetPos();
}
