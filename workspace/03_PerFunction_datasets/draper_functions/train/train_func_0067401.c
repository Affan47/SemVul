qmonFreeSMData(
tSMEntry *data
) {
   DENTER(GUI_LAYER, "qmonFreeSMData");

   if (data->job_script) {
      XtFree((char*)data->job_script);
      data->job_script = NULL;
   }

   if (data->job_tasks) {
      XtFree((char*)data->job_tasks);
      data->job_tasks = NULL;
   }


   if (data->job_name) {
      XtFree((char*)data->job_name);
      data->job_name = NULL;
   }

   if (data->project) {
      XtFree((char*)data->project);
      data->project = NULL;
   }

   if (data->ckpt_obj) {
      XtFree((char*)data->ckpt_obj);
      data->ckpt_obj = NULL;
   }


   if (data->directive_prefix) {
      XtFree((char*)data->directive_prefix);
      data->directive_prefix = NULL;
   }

   if (data->cell) {
      XtFree((char*)data->cell);
      data->cell = NULL;
   }

   if (data->account_string) {
      XtFree((char*)data->account_string);
      data->account_string = NULL;
   }

   if (data->wd_path) {
      XtFree((char*)data->wd_path);
      data->wd_path = NULL;
   }

   if (data->jsv_url) {
      XtFree((char*)data->jsv_url);
      data->jsv_url = NULL;
   }

   if (data->binding) {
      XtFree((char*)data->binding);
      data->binding = NULL;
   }

   if (data->pe) {
      XtFree((char*)data->pe);
      data->pe = NULL;
   }

   lFreeList(&(data->task_range));

   lFreeList(&(data->job_args));

   lFreeList(&(data->shell_list));

   lFreeList(&(data->mail_list));

   lFreeList(&(data->stdoutput_path_list));

   lFreeList(&(data->stdinput_path_list));

   lFreeList(&(data->stderror_path_list));

   lFreeList(&(data->hard_resource_list));

   lFreeList(&(data->soft_resource_list));

   lFreeList(&(data->hard_queue_list));

   lFreeList(&(data->soft_queue_list));

   lFreeList(&(data->master_queue_list));

   lFreeList(&(data->hold_jid));

   lFreeList(&(data->hold_jid_ad));

   lFreeList(&(data->env_list));

   lFreeList(&(data->ctx_list));

   DEXIT;
}
