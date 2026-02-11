job_check_correct_id_sublists(lListElem *job, lList **answer_list)
{
   DENTER(TOP_LAYER, "job_check_correct_id_sublists");


   {
      const int field[] = {
         JB_ja_structure,
         JB_ja_n_h_ids,
         JB_ja_u_h_ids,
         JB_ja_s_h_ids,
         JB_ja_o_h_ids,
         JB_ja_a_h_ids,
         JB_ja_z_ids,
         -1
      };
      int i = -1;

      while (field[++i] != -1) {
         lList *range_list = lGetList(job, field[i]);
         lListElem *range = NULL;

         for_each(range, range_list) {
            if (field[i] != JB_ja_structure)
               range_correct_end(range);
            if (range_is_id_within(range, 0)) {
               ERROR((SGE_EVENT, MSG_JOB_NULLNOTALLOWEDT));
               answer_list_add(answer_list, SGE_EVENT, STATUS_EUNKNOWN,
                               ANSWER_QUALITY_ERROR);
               DRETURN_VOID;
            }
         }
      }
   }


   {
      const int field[] = {
         JB_ja_n_h_ids,
         JB_ja_u_h_ids,
         JB_ja_s_h_ids,
         JB_ja_o_h_ids,
         JB_ja_a_h_ids,
         -1
      };
      int has_structure = 0;
      int has_x_ids = 0;
      int i = -1;

      while (field[++i] != -1) {
         lList *range_list = lGetList(job, field[i]);

         if (!range_list_is_empty(range_list)) {
            has_x_ids = 1;
         }
      }
      has_structure = !range_list_is_empty(lGetList(job, JB_ja_structure));
      if (!has_structure) {
         ERROR((SGE_EVENT, MSG_JOB_NOIDNOTALLOWED));
         answer_list_add(answer_list, SGE_EVENT, STATUS_EUNKNOWN,
                         ANSWER_QUALITY_ERROR);
         DRETURN_VOID;
      } else if (!has_x_ids) {
         job_initialize_id_lists(job, answer_list);
      }
   }

   DRETURN_VOID;
}
