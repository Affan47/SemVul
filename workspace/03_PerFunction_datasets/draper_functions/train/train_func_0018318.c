update_wait_time(JCR *jcr, int newJobStatus)
{
   bool enter_in_waittime;
   int oldJobStatus = jcr->JobStatus;

   switch (newJobStatus) {
   case JS_WaitFD:
   case JS_WaitSD:
   case JS_WaitMedia:
   case JS_WaitMount:
   case JS_WaitStoreRes:
   case JS_WaitJobRes:
   case JS_WaitClientRes:
   case JS_WaitMaxJobs:
   case JS_WaitPriority:
      enter_in_waittime = true;
      break;
   default:
      enter_in_waittime = false;
      break;
   }


   switch (oldJobStatus) {
   case JS_WaitFD:
   case JS_WaitSD:
   case JS_WaitMedia:
   case JS_WaitMount:
   case JS_WaitStoreRes:
   case JS_WaitJobRes:
   case JS_WaitClientRes:
   case JS_WaitMaxJobs:
   case JS_WaitPriority:
      if (!enter_in_waittime) {
         jcr->wait_time_sum += (time(NULL) - jcr->wait_time);
         jcr->wait_time = 0;
      }
      break;


   default:
      if (enter_in_waittime) {
         jcr->wait_time = time(NULL);
      }
      break;
   }
}
