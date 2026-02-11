lookup_counter_var(var_t *ctx, void *my_ctx,
          const char *var_ptr, int var_len, int var_inc, int var_index,
          const char **val_ptr, int *val_len, int *val_size)
{
   char buf[MAXSTRING];
   var_rc_t stat = VAR_ERR_UNDEFINED_VARIABLE;

   if (var_len > (int)sizeof(buf) - 1) {
       return VAR_ERR_OUT_OF_MEMORY;
   }
   memcpy(buf, var_ptr, var_len);
   buf[var_len] = 0;
   LockRes();
   for (COUNTER *counter=NULL; (counter = (COUNTER *)GetNextRes(R_COUNTER, (RES *)counter)); ) {
      if (strcmp(counter->name(), buf) == 0) {
         Dmsg2(100, "Counter=%s val=%d\n", buf, counter->CurrentValue);

        if (var_index == -1) {
            bsnprintf(buf, sizeof(buf), "%d", counter->CurrentValue);
            *val_len = bsnprintf(buf, sizeof(buf), "%d", strlen(buf));
            *val_ptr = buf;
            *val_size = 0;
            return VAR_OK;
         } else {
            bsnprintf(buf, sizeof(buf), "%d", counter->CurrentValue);
            *val_ptr = bstrdup(buf);
            *val_len = strlen(buf);
            *val_size = *val_len + 1;
         }
         if (var_inc) {
            if (counter->CurrentValue == counter->MaxValue) {
               counter->CurrentValue = counter->MinValue;
            } else {
               counter->CurrentValue++;
            }
            if (counter->Catalog) {
               COUNTER_DBR cr;
               JCR *jcr = (JCR *)my_ctx;
               memset(&cr, 0, sizeof(cr));
               bstrncpy(cr.Counter, counter->name(), sizeof(cr.Counter));
               cr.MinValue = counter->MinValue;
               cr.MaxValue = counter->MaxValue;
               cr.CurrentValue = counter->CurrentValue;
               Dmsg1(100, "New value=%d\n", cr.CurrentValue);
               if (counter->WrapCounter) {
                  bstrncpy(cr.WrapCounter, counter->WrapCounter->name(), sizeof(cr.WrapCounter));
               } else {
                  cr.WrapCounter[0] = 0;
               }
               if (!db_update_counter_record(jcr, jcr->db, &cr)) {
                  Jmsg(jcr, M_ERROR, 0, _("Count not update counter %s: ERR=%s\n"),
                     counter->name(), db_strerror(jcr->db));
               }
            }
         }
         stat = VAR_OK;
         break;
      }
   }
   UnlockRes();
   return stat;
}
