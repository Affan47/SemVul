FormatBytesTimeRate(off_t bytes,double time_spent)
{
   if(bytes<=0)
      return "";

   if(time_spent>=1)
   {
      xstring& msg=xstring::format(
	 plural("%lld $#ll#byte|bytes$ transferred in %ld $#l#second|seconds$",
		     (long long)bytes,long(time_spent+.5)),
		     (long long)bytes,long(time_spent+.5));
      double rate=bytes/time_spent;
      if(rate>=1)
	 msg.appendf(" (%s)",Speedometer::GetStr(rate).get());
      return msg;
   }
   return xstring::format(plural("%lld $#ll#byte|bytes$ transferred",
		     (long long)bytes),(long long)bytes);
}
