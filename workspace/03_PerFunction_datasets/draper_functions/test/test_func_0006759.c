remove_tagged_jobs(lList *job_list) {

   lListElem *jep = lFirst(job_list);
   lListElem *tmp = NULL;

   while (jep) {
      lList *task_list;
      lListElem *jatep, *tmp_jatep;

      tmp = lNext(jep);
      task_list = lGetList(jep, JB_ja_tasks);
      jatep = lFirst(task_list);
      while (jatep) {
         tmp_jatep = lNext(jatep);
         if ((lGetUlong(jatep, JAT_suitable) & TAG_FOUND_IT)) {
            lRemoveElem(task_list, &jatep);
         }
         jatep = tmp_jatep;
      }
      jep = tmp;
   }

}
