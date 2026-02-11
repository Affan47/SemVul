suser_job_count(const lListElem *job)
{
   const char *submit_user = NULL;
   lListElem *suser = NULL;
   int ret = 0;

   DENTER(TOP_LAYER, "suser_job_job");
   submit_user = lGetString(job, JB_owner);
   suser = suser_list_find(*object_type_get_master_list(SGE_TYPE_SUSER), submit_user);
   if (suser != NULL) {
      ret = suser_get_job_counter(suser);
   }
   DEXIT;
   return ret;
}
