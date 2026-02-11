sge_rebuild_job_category(lList *job_list, lList *acl_list, const lList *prj_list, const lList *rqs_list)
{
   lListElem *job;

   DENTER(TOP_LAYER, "sge_rebuild_job_category");

   if (!reb_cat) {
      DRETURN(0);
   }

   DPRINTF(("### ### ### ###   REBUILDING CATEGORIES   ### ### ### ###\n"));

   lFreeList(&CATEGORY_LIST);
   lFreeList(&CS_CATEGORY_LIST);

   for_each (job, job_list) {
      sge_add_job_category(job, acl_list, prj_list, rqs_list);
   }

   reb_cat = false;

   DRETURN(0);
}
