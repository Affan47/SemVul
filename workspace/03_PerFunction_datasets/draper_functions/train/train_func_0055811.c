qinstance_state_as_string(u_long32 bit)
{
   static const u_long32 states[] = {
      QI_ALARM,
      QI_SUSPEND_ALARM,
      QI_DISABLED,
      QI_SUSPENDED,
      QI_UNKNOWN,
      QI_ERROR,
      QI_SUSPENDED_ON_SUBORDINATE,
      QI_CAL_DISABLED,
      QI_CAL_SUSPENDED,
      QI_AMBIGUOUS,
      QI_ORPHANED,

      (u_long32)~QI_ALARM,
      (u_long32)~QI_SUSPEND_ALARM,
      (u_long32)~QI_DISABLED,
      (u_long32)~QI_SUSPENDED,
      (u_long32)~QI_UNKNOWN,
      (u_long32)~QI_ERROR,
      (u_long32)~QI_SUSPENDED_ON_SUBORDINATE,
      (u_long32)~QI_CAL_DISABLED,
      (u_long32)~QI_CAL_SUSPENDED,
      (u_long32)~QI_AMBIGUOUS,
      (u_long32)~QI_ORPHANED,


      0
   };
   static const char *names[23] = { NULL };
   const char *ret = NULL;
   int i = 0;

   DENTER(TOP_LAYER, "qinstance_state_as_string");
   if (names[0] == NULL) {
      names[0] = MSG_QINSTANCE_ALARM;
      names[1] = MSG_QINSTANCE_SUSPALARM;
      names[2] = MSG_QINSTANCE_DISABLED;
      names[3] = MSG_QINSTANCE_SUSPENDED;
      names[4] = MSG_QINSTANCE_UNKNOWN;
      names[5] = MSG_QINSTANCE_ERROR;
      names[6] = MSG_QINSTANCE_SUSPOSUB;
      names[7] = MSG_QINSTANCE_CALDIS;
      names[8] = MSG_QINSTANCE_CALSUSP;
      names[9] = MSG_QINSTANCE_CONFAMB;
      names[10] = MSG_QINSTANCE_ORPHANED;
      names[11] = MSG_QINSTANCE_NALARM;
      names[12] = MSG_QINSTANCE_NSUSPALARM;
      names[13] = MSG_QINSTANCE_NDISABLED;
      names[14] = MSG_QINSTANCE_NSUSPENDED;
      names[15] = MSG_QINSTANCE_NUNKNOWN;
      names[16] = MSG_QINSTANCE_NERROR;
      names[17] = MSG_QINSTANCE_NSUSPOSUB;
      names[18] = MSG_QINSTANCE_NCALDIS;
      names[19] = MSG_QINSTANCE_NCALSUSP;
      names[20] = MSG_QINSTANCE_NCONFAMB;
      names[21] = MSG_QINSTANCE_NORPHANED;
      names[22] = NULL;
   }

   while (states[i] != 0) {
      if (states[i] == bit) {
         ret = names[i];
         break;
      }
      i++;
   }
   DEXIT;
   return ret;
}
