nccf_def_file(int ncid, const char *title, const char *history)
{
   int ret;


   if ((ret = nccf_def_convention(ncid)))
      return ret;


   if (title)
      if ((ret = nc_put_att_text(ncid, NC_GLOBAL, CF_TITLE,
				    strlen(title) + 1, title)))
	 return ret;


   if (history)
      ret = nccf_add_history(ncid, history);

   return ret;
}
