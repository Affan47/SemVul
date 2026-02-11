_ecore_file_download_url_progress_cb(void *data __UNUSED__, int type __UNUSED__, void *event)
{


   Ecore_Con_Event_Url_Progress *ev = event;
   Ecore_File_Download_Job      *job;

   job = eina_list_search_unsorted(_job_list, _ecore_file_download_url_compare_job, ev->url_con);
   if (!ECORE_MAGIC_CHECK(job, ECORE_MAGIC_FILE_DOWNLOAD_JOB)) return ECORE_CALLBACK_PASS_ON;

   if (job->progress_cb)
     if (job->progress_cb(ecore_con_url_data_get(job->url_con), job->dst,
                          (long int) ev->down.total, (long int) ev->down.now,
                          (long int) ev->up.total, (long int) ev->up.now) != 0)
       {
          _job_list = eina_list_remove(_job_list, job);
          fclose(job->file);
          free(job->dst);
          free(job);

          return ECORE_CALLBACK_PASS_ON;
       }

   return ECORE_CALLBACK_DONE;
}
