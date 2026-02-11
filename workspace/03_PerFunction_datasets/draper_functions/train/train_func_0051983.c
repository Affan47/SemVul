spool_delete_script(lList **answer_list, u_long32 jobid, lListElem *jep)
{
   bool ret=true;
   dstring buffer = DSTRING_INIT;
   DENTER(TOP_LAYER, "spool_delete_script");
   PROF_START_MEASUREMENT(SGE_PROF_JOBSCRIPT);
   ret = spool_delete_object(answer_list, spool_get_default_context(),
                  SGE_TYPE_JOBSCRIPT, jobscript_get_key(jep, &buffer), true);
   PROF_STOP_MEASUREMENT(SGE_PROF_JOBSCRIPT);
   sge_dstring_free(&buffer);
   lSetString(jep, JB_exec_file, NULL);
   lSetString(jep, JB_script_file, NULL);
   lSetUlong(jep, JB_script_size, 0);
   DRETURN(ret);
}
