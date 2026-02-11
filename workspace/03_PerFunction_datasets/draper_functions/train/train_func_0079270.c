guess_highest_job_number()
{
   lListElem *jep;
   u_long32 maxid = 0;
   int pos;
   lList *master_job_list = *(object_type_get_master_list(SGE_TYPE_JOB));

   DENTER(TOP_LAYER, "guess_highest_job_number");


   SGE_LOCK(LOCK_GLOBAL, LOCK_READ);

   jep = lFirst(master_job_list);
   if (jep) {
      pos = lGetPosViaElem(jep, JB_job_number, SGE_NO_ABORT);

      for_each(jep, master_job_list) {
         maxid = MAX(maxid, lGetPosUlong(jep, pos));
      }
   }

   SGE_UNLOCK(LOCK_GLOBAL, LOCK_READ);

   DRETURN(maxid);
}
