name(void) const
{
   if(!validurl)
     const_cast<GURL *>(this)->init();
   GUTF8String retval;
   if(!is_empty())
   {
     const GUTF8String xurl(url);
     const int protocol_length=protocol(xurl).length();
     const char * ptr, * xslash=(const char *)xurl+protocol_length-1;
     for(ptr=(const char *)xurl+protocol_length;
       *ptr && !is_argument(ptr);ptr++)
	 {
       if (*ptr==slash)
          xslash=ptr;
	 }
     retval=GUTF8String(xslash+1, ptr-xslash-1);
   }
   return retval;
}
