store_cgi_args(void)


{
   if(!validurl)
     init();
   GCriticalSectionLock lock1(&class_lock);

   const char * const url_ptr=url;
   const char * ptr;
   for(ptr=url_ptr;*ptr&&(*ptr!='?');ptr++)
   		EMPTY_LOOP;

   GUTF8String new_url(url_ptr, ptr-url_ptr);

   for(int i=0;i<cgi_name_arr.size();i++)
   {
      GUTF8String name=GURL::encode_reserved(cgi_name_arr[i]);
      GUTF8String value=GURL::encode_reserved(cgi_value_arr[i]);
      new_url+=(i?"&":"?")+name;
      if (value.length())
         new_url+="="+value;
   }

   url=new_url;
}
