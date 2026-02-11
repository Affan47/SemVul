FormatFinalWithPrefix(xstring& s,const char *p)
{
   if(no_status)
      return s;
   if(count==errors)
      return s;
   if(bytes)
      s.appendf("%s%s\n",p,CopyJob::FormatBytesTimeRate(bytes,time_spent));
   if(errors>0)
   {
      s.append(p);
      s.appendf(plural("Transfer of %d of %d $file|files$ failed\n",count),
	 errors,count);
   }
   else if(count>1)
   {
      s.append(p);
      s.appendf(plural("Total %d $file|files$ transferred\n",count),count);
   }
   return s;
}
