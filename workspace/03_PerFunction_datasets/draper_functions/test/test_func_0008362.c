try_csm_proxy(file_info &info,const char *str)
{
   info.clear();

   int n;
   int status = false;
   char additional_file_info[33];
   int has_additional_file_info = false;

   memset(additional_file_info, '\0', sizeof (additional_file_info));


   if (5 <= (n = sscanf(str,"%lld %3s %d %2d:%2d%32s",
	       &info.size, info.month_name, &info.day, &info.hour, &info.minute, additional_file_info))) {
      status = true;
      if (6 == n)
	  has_additional_file_info = true;
   } else {

       info.clear();
       if (4 <= (n = sscanf(str,"%lld %3s %d %4d%32s",
		       &info.size, info.month_name, &info.day, &info.year, additional_file_info))) {
	   status = true;
	   if (5 == n)
	       has_additional_file_info = true;
       }
   }

   if (status) {
      debug("csm_proxy listing matched");
      snprintf(info.size_str,sizeof(info.size_str),"%lld",info.size);
      if (has_additional_file_info && additional_file_info[0]) {
	  if (!strncasecmp("Symbolic Link",additional_file_info,13)) {
	      info.is_sym_link = true;
	  } else if (!strncasecmp("Directory",additional_file_info,9)) {
	      info.is_directory = true;
	  } else {

	      Log::global->Format(10,
		      "* try_csm_proxy: unknown file type '%s'\n",
		      additional_file_info);
	  }
      }
   }
   return status;
}
