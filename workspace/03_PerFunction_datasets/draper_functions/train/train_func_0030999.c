job_is_tight_parallel(const lListElem *job, const lList *pe_list)
{
   bool ret = false;
   const char *pe_name = NULL;

   DENTER(TOP_LAYER, "job_is_tight_parallel");
   pe_name = lGetString(job, JB_pe);
   if (pe_name != NULL) {
      int found_pe = 0;
      int all_are_tight = 1;
      lListElem *pe;

      for_each(pe, pe_list) {
         if (pe_is_matching(pe, pe_name)) {
            found_pe = 1;
            all_are_tight &= lGetBool(pe, PE_control_slaves);
         }
      }

      if (found_pe && all_are_tight) {
         ret = true;
      }
   }
   DRETURN(ret);
}
