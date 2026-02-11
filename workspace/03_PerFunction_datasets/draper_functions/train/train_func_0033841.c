try_apache_listing(file_info &info,const char *str)
{
   info.clear();


   int n=sscanf(str,"%2d-%3s-%4d %2d:%2d %30s",
	       &info.day,info.month_name,&info.year,
	       &info.hour,&info.minute,info.size_str);
   if(n==6 && (info.size_str[0]=='-' || is_ascii_digit(info.size_str[0])))
   {
      debug("apache listing matched");
      return true;
   }
   return false;
}
