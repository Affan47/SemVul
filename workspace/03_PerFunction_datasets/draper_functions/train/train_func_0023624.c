extended_parse_ulong_val(double *dvalp, u_long32 *uvalp, u_long32 type,
                             const char *s, char *error_str, int error_len,
                             int enable_infinity, bool only_positive)
{
   int retval = 0;
   char dummy[10];
   u_long32 dummy_uval;

   if (s == NULL) {
      return 0;
   }

   if (only_positive && (strchr(s, '-') != NULL)) {
      if (error_str) {
         sge_strlcpy(error_str, MSG_GDI_NUMERICALVALUENOTPOSITIVE, error_len);
      }
      return 0;
   }

   if ((enable_infinity == 0) && (strcasecmp(s,"infinity") == 0)) {
      if (error_str) {
         sge_strlcpy(error_str, MSG_GDI_VALUETHATCANBESETTOINF, error_len);
      }
      return 0;
   }

   if (uvalp == NULL) {
      uvalp = &dummy_uval;
   }


   switch (type) {
   case TYPE_LOG:
      retval = sge_parse_loglevel_val(uvalp, s);
      if (retval != 1) {
         if (error_str != NULL) {
            sge_strlcpy(error_str, "loglevel value", error_len);
         }
      }
      break;

   case TYPE_INT:
   case TYPE_TIM:
   case TYPE_MEM:
   case TYPE_BOO:
   case TYPE_DOUBLE:

      if (error_str != NULL) {
         *uvalp = sge_parse_num_val(NULL, dvalp, s, s, error_str, error_len);
         if (!error_str[0])
            retval = 1;
         else {
            if (type==TYPE_INT)
               sge_strlcpy(error_str, "integer value", error_len);
            else if (type==TYPE_TIM)
               sge_strlcpy(error_str, "time value", error_len);
            else if (type==TYPE_BOO)
               sge_strlcpy(error_str, "boolean value", error_len);
            else if (type==TYPE_DOUBLE)
               sge_strlcpy(error_str, "double value", error_len);
            else
               sge_strlcpy(error_str, "memory value", error_len);
         }
      } else {
         dummy[0] = '\0';
         *uvalp = sge_parse_num_val(NULL, dvalp, s, s, dummy, sizeof(dummy));
         if (!dummy[0]) {
            retval = 1;
         }
      }
      break;

   default:
      break;
   }
   return retval;
}
