task_ref_copy_to_ja_task(sge_task_ref_t *tref, lListElem *ja_task)
{

   DENTER(BASIS_LAYER, "task_ref_copy_to_ja_task");

   if (ja_task != NULL && tref != NULL) {
      lSetUlong(ja_task, JAT_task_number, tref->ja_task_number);

      lSetDouble(ja_task, JAT_tix,                       tref->ja_task_ticket);
      lSetDouble(ja_task, JAT_fticket,                   tref->ja_task_fticket);
      lSetDouble(ja_task, JAT_sticket,                   tref->ja_task_sticket);
      lSetDouble(ja_task, JAT_oticket,                   tref->ja_task_oticket);
      lSetDouble(ja_task, JAT_share,                     tref->ja_task_share);
      lSetUlong(ja_task, JAT_fshare,                     tref->ja_task_fshare);

   }
   DEXIT;
}
