ckpt_is_referenced(const lListElem *ckpt, lList **answer_list,
                        const lList *master_job_list,
                        const lList *master_cqueue_list)
{
   bool ret = false;

   {
      lListElem *job = NULL;

      for_each(job, master_job_list) {
         if (job_is_ckpt_referenced(job, ckpt)) {
            const char *ckpt_name = lGetString(ckpt, CK_name);
            u_long32 job_id = lGetUlong(job, JB_job_number);

            answer_list_add_sprintf(answer_list, STATUS_EUNKNOWN,
                                    ANSWER_QUALITY_INFO, MSG_CKPTREFINJOB_SU,
                                    ckpt_name, sge_u32c(job_id));
            ret = true;
            break;
         }
      }
   }
   if (!ret) {
      lListElem *queue = NULL, *ckl = NULL;


      const char *ckpt_name = lGetString(ckpt, CK_name);

      for_each(queue, master_cqueue_list) {
         for_each(ckl, lGetList(queue, CQ_ckpt_list)){
            if (lGetSubStr(ckl, ST_name, ckpt_name, ASTRLIST_value))  {
               answer_list_add_sprintf(answer_list, STATUS_EUNKNOWN,
                                       ANSWER_QUALITY_INFO,
                                       MSG_CKPTREFINQUEUE_SS,
                                       ckpt_name, lGetString(queue, CQ_name));
               ret = true;
               break;
            }
         }
      }
   }
   return ret;
}
