AH_Outbox__CBox_HandleQueueListError(AH_OUTBOX__CBOX *cbox,
                                          AH_JOBQUEUE_LIST *jql,
                                          const char *logStr){
  AH_JOBQUEUE *jq;

  while((jq=AH_JobQueue_List_First(jql))) {
    AH_JobQueue_List_Del(jq);
    AH_Outbox__CBox_HandleQueueError(cbox, jq, logStr);
  }
  AH_JobQueue_List_free(jql);
}
