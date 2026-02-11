jobstatus_to_ascii_gui(int JobStatus, char *msg, int maxlen)
{
   const char *cnv = NULL;
   switch (JobStatus) {
   case JS_Terminated:
      cnv = _("Completed successfully");
      break;
   case JS_Warnings:
      cnv = _("Completed with warnings");
      break;
   case JS_ErrorTerminated:
      cnv = _("Terminated with errors");
      break;
   case JS_FatalError:
      cnv = _("Fatal error");
      break;
   case JS_Created:
      cnv = _("Created, not yet running");
      break;
   case JS_Canceled:
      cnv = _("Canceled by user");
      break;
   case JS_Differences:
      cnv = _("Verify found differences");
      break;
   case JS_WaitFD:
      cnv = _("Waiting for File daemon");
      break;
   case JS_WaitSD:
      cnv = _("Waiting for Storage daemon");
      break;
   case JS_WaitPriority:
      cnv = _("Waiting for higher priority jobs");
      break;
   case JS_AttrInserting:
      cnv = _("Batch inserting file records");
      break;
   };

   if (cnv) {
      bstrncpy(msg, cnv, maxlen);
   } else {
     jobstatus_to_ascii(JobStatus, msg, maxlen);
   }
}
