CloseLog()
{
   char timestr[200];
   time_t t = time(NULL);
   struct tm *tmp = localtime(&t);
   strftime(timestr, sizeof(timestr), "%F  %T", tmp);

   if(d->term_out)
   {
      fprintf(d->term_out, "Log ended: ");
      fprintf(d->term_out, "%s", timestr);
      fprintf(d->term_out, "\n");
      fclose(d->term_out);
   }
   d->term_out = NULL;

   if(d->history_out)
   {
      if (disappearedPkgs.empty() == false)
      {
	 string disappear;
	 for (std::set<std::string>::const_iterator d = disappearedPkgs.begin();
	      d != disappearedPkgs.end(); ++d)
	 {
	    pkgCache::PkgIterator P = Cache.FindPkg(*d);
	    disappear.append(*d);
	    if (P.end() == true)
	       disappear.append(", ");
	    else
	       disappear.append(" (").append(Cache[P].CurVersion).append("), ");
	 }
	 WriteHistoryTag("Disappeared", disappear);
      }
      if (d->dpkg_error.empty() == false)
	 fprintf(d->history_out, "Error: %s\n", d->dpkg_error.c_str());
      fprintf(d->history_out, "End-Date: %s\n", timestr);
      fclose(d->history_out);
   }
   d->history_out = NULL;

   return true;
}
