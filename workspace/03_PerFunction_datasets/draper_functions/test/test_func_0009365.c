qrstat_filter_add_ar_where(qrstat_env_t *qrstat_env)
{
   lCondition *where = NULL;
   lListElem *elem = NULL;

   DENTER(TOP_LAYER, "qrstat_filter_add_ar_where");
   for_each(elem, qrstat_env->ar_id_list) {
      lCondition *tmp_where = NULL;
      u_long32 value = lGetUlong(elem, ULNG_value);

      tmp_where = lWhere("%T(%I == %u)", AR_Type, AR_id, value);
      if (tmp_where != NULL) {
         if (where == NULL) {
            where = tmp_where;
         } else {
            where = lOrWhere(where, tmp_where);
         }
      }
   }
   if (where != NULL) {
      if (qrstat_env->where_AR_Type == NULL) {
         qrstat_env->where_AR_Type = where;
      } else {
         qrstat_env->where_AR_Type = lAndWhere(qrstat_env->where_AR_Type, where);
      }
   }
   DRETURN_VOID;
}
