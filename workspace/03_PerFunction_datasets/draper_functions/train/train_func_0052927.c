japi_sync_job_tasks(lListElem *japi_job, lListElem *sge_job)
{
   lList *range_list_copy = NULL;
   lListElem *range = NULL;
   lListElem *task = NULL;
   u_long32 min = 0;
   u_long32 max = 0;
   u_long32 step = 0;
   u_long32 taskid = 0;
   int finished_tasks = 0;


   DENTER (TOP_LAYER, "japi_sync_job_tasks");


   range_list_copy = lCopyList(NULL, lGetList(japi_job, JJ_not_yet_finished_ids));


   for_each (range, range_list_copy) {
      range_get_all_ids(range, &min, &max, &step);

      for (taskid = min; taskid <= max; taskid += step) {
         task = job_search_task(sge_job, NULL, taskid);
         if (task != NULL) {
            DPRINTF(("task "sge_u32"."sge_u32" contained in enrolled task list\n",
                     lGetUlong(japi_job, JJ_jobid), taskid));

            if ((lGetUlong(task, JAT_status) & JFINISHED) != 0) {
               DPRINTF(("task "sge_u32"."sge_u32" is finished\n",
                        lGetUlong(japi_job, JJ_jobid), taskid));
            }


            else if ((lGetUlong(task, JAT_state) & JERROR) != 0) {
               DPRINTF(("task "sge_u32"."sge_u32" has failed\n",
                        lGetUlong(japi_job, JJ_jobid), taskid));
            }
            else {
               continue;
            }
         }
         else if (range_list_is_id_within(lGetList(sge_job, JB_ja_n_h_ids), taskid) ||
                  range_list_is_id_within(lGetList(sge_job, JB_ja_u_h_ids), taskid) ||
                  range_list_is_id_within(lGetList(sge_job, JB_ja_s_h_ids), taskid) ||
                  range_list_is_id_within(lGetList(sge_job, JB_ja_o_h_ids), taskid)) {
            DPRINTF(("task "sge_u32"."sge_u32" is still pending\n",
                     lGetUlong(japi_job, JJ_jobid), taskid));
            continue;
         }
         else {
            if (range_list_is_id_within(lGetList(sge_job, JB_ja_z_ids), taskid)) {
               DPRINTF(("task "sge_u32"."sge_u32" contained in zombie list taskid list\n",
                        lGetUlong(japi_job, JJ_jobid), taskid));
            }

            DPRINTF(("task "sge_u32"."sge_u32" presumably has finished meanwhile\n",
                     lGetUlong(japi_job, JJ_jobid), taskid));
         }


         object_delete_range_id(japi_job, NULL, JJ_not_yet_finished_ids,
                                taskid);

         DPRINTF(("adding finished task %ld for job %ld which still exists\n",
                  taskid, lGetUlong(japi_job, JJ_jobid)));
         lAddSubUlong(japi_job, JJAT_task_id, taskid, JJ_finished_tasks,
                      JJAT_Type);
         finished_tasks++;
      }
   }

   lFreeList(&range_list_copy);
   DRETURN(finished_tasks);
}
