reporting_get_double_usage(const lList *usage_list, lList *reported_list,
                           const char *name, const char *rname, double def)
{

   double usage = usage_list_get_double_usage(usage_list, name, def);

   if (reported_list != NULL) {
      double reported;


      reported = usage_list_get_double_usage(reported_list, rname, def);


      usage_list_set_double_usage(reported_list, rname, usage);


      usage -= reported;
   }

   return usage;
}
