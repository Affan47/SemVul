analyze_jatask_event(sge_evc_class_t *evc, object_description *object_base,sge_object_type type,
                     sge_event_action action, lListElem *event, void *clientdata)
{
   char buffer[1024];
   dstring buffer_wrapper;

   sge_dstring_init(&buffer_wrapper, buffer, sizeof(buffer));

   if (lGetPosViaElem(event, ET_type, SGE_NO_ABORT) >= 0) {
      u_long32 type = lGetUlong(event, ET_type);

      if (type == sgeE_JATASK_MOD) {
         lList *jat = lGetList(event,ET_new_version);
         lListElem *ep = lFirst(jat);
         u_long job_status = lGetUlong(ep, JAT_status);
         int task_running = (job_status==JRUNNING || job_status==JTRANSFERING);
         if (task_running) {
         }
      }

      if (type == sgeE_JOB_FINAL_USAGE) {
      }

      if (type == sgeE_JOB_ADD) {


      }

      if (type == sgeE_JOB_DEL) {
         qevent_trigger_scripts(QEVENT_JB_END, qevent_get_option_struct(), event);
      }

      if (type == sgeE_JATASK_DEL) {
         qevent_trigger_scripts(QEVENT_JB_TASK_END,qevent_get_option_struct() , event);
      }


   }

   if(type == SGE_TYPE_GLOBAL_CONFIG) {
      return SGE_EMA_FAILURE;
   }

   return SGE_EMA_OK;
}
