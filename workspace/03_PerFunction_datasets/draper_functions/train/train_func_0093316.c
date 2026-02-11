job_has_to_spool_one_file(const lListElem *job,
                                     const lList *pe_list,
                                     sge_spool_flags_t flags)
{
   DENTER(TOP_LAYER, "job_has_to_spool_one_file");

   if ((flags & SPOOL_HANDLE_AS_ZOMBIE) || (flags & SPOOL_WITHIN_EXECD)) {
      DRETURN(1);
   }

   if (job_might_be_tight_parallel(job, pe_list)
               || (job_get_submit_ja_tasks(job) > sge_get_ja_tasks_per_file())) {
      DRETURN(0);
   }

   DRETURN(1);
}
