reporting_get_job_log_name(const job_log_t type)
{
   const char *ret;

   switch (type) {
      case JL_UNKNOWN:
         ret = MSG_JOBLOG_ACTION_UNKNOWN;
         break;
      case JL_PENDING:
         ret = MSG_JOBLOG_ACTION_PENDING;
         break;
      case JL_SENT:
         ret = MSG_JOBLOG_ACTION_SENT;
         break;
      case JL_RESENT:
         ret = MSG_JOBLOG_ACTION_RESENT;
         break;
      case JL_DELIVERED:
         ret = MSG_JOBLOG_ACTION_DELIVERED;
         break;
      case JL_RUNNING:
         ret = MSG_JOBLOG_ACTION_RUNNING;
         break;
      case JL_SUSPENDED:
         ret = MSG_JOBLOG_ACTION_SUSPENDED;
         break;
      case JL_UNSUSPENDED:
         ret = MSG_JOBLOG_ACTION_UNSUSPENDED;
         break;
      case JL_HELD:
         ret = MSG_JOBLOG_ACTION_HELD;
         break;
      case JL_RELEASED:
         ret = MSG_JOBLOG_ACTION_RELEASED;
         break;
      case JL_RESTART:
         ret = MSG_JOBLOG_ACTION_RESTART;
         break;
      case JL_MIGRATE:
         ret = MSG_JOBLOG_ACTION_MIGRATE;
         break;
      case JL_DELETED:
         ret = MSG_JOBLOG_ACTION_DELETED;
         break;
      case JL_FINISHED:
         ret = MSG_JOBLOG_ACTION_FINISHED;
         break;
      case JL_ERROR:
         ret = MSG_JOBLOG_ACTION_ERROR;
         break;
      default:
         ret = "!!!! unknown job state !!!!";
         break;
   }

   return ret;
}
