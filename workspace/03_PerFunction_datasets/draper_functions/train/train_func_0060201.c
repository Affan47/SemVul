ar_get_string_from_event(ar_state_event_t event)
{
   const char *ret = MSG_AR_EVENT_STATE_UNKNOWN;
   DENTER(TOP_LAYER, "ar_get_string_from_event");
   switch(event) {
      case ARL_UNKNOWN:
         ret = MSG_AR_EVENT_STATE_UNKNOWN;
         break;
      case ARL_CREATION:
         ret = MSG_AR_EVENT_STATE_CREATION;
         break;
      case ARL_STARTTIME_REACHED:
         ret = MSG_AR_EVENT_STATE_STARTIME_REACHED;
         break;
      case ARL_ENDTIME_REACHED:
         ret = MSG_AR_EVENT_STATE_ENDTIME_REACHED;
         break;
      case ARL_UNSATISFIED:
         ret = MSG_AR_EVENT_STATE_UNSATISFIED;
         break;
      case ARL_OK:
         ret = MSG_AR_EVENT_STATE_OK;
         break;
      case ARL_TERMINATED:
         ret = MSG_AR_EVENT_STATE_TERMINATED;
         break;
      case ARL_DELETED:
         ret = MSG_AR_EVENT_STATE_DELETED;
         break;
      default:

         DTRACE;
         break;
   }
   DRETURN(ret);
}
