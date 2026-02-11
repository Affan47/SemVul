lookup_var(var_t *ctx, void *my_ctx,
          const char *var_ptr, int var_len, int var_inc, int var_index,
          const char **val_ptr, int *val_len, int *val_size)
{
   char buf[MAXSTRING], *val, *p, *v;
   var_rc_t stat;
   int count;


   if ((stat = lookup_built_in_var(ctx, my_ctx, var_ptr, var_len, var_index,
        val_ptr, val_len, val_size)) == VAR_OK) {
      return VAR_OK;
   }

   if ((stat = lookup_counter_var(ctx, my_ctx, var_ptr, var_len, var_inc, var_index,
        val_ptr, val_len, val_size)) == VAR_OK) {
      return VAR_OK;
   }


   if (var_len > (int)sizeof(buf) - 1) {
       return VAR_ERR_OUT_OF_MEMORY;
   }
   memcpy(buf, var_ptr, var_len + 1);
   buf[var_len] = 0;
   Dmsg1(100, "Var=%s\n", buf);

   if ((val = getenv(buf)) == NULL) {
       return VAR_ERR_UNDEFINED_VARIABLE;
   }

   count = 1;


   for (p = val; *p; p++) {
      if (*p == '|') {
         count++;
      }
   }
   Dmsg3(100, "For %s, reqest index=%d have=%d\n",
      buf, var_index, count);


   if (var_index == -1) {
      int len;
      if (count == 1) {
         len = strlen(val);
      } else {
         len = count;
      }
      *val_len = bsnprintf(buf, sizeof(buf), "%d", len);
      *val_ptr = buf;
      *val_size = 0;
      return VAR_OK;
   }


   if (var_index < -1 || var_index > --count) {

      return VAR_ERR_UNDEFINED_VARIABLE;
   }

   count = 0;
   for (p=val; *p; ) {
      if (*p == '|') {
         if (count < var_index) {
            val = ++p;
            count++;
            continue;
         }
         break;
      }
      p++;
   }
   if (p-val > (int)sizeof(buf) - 1) {
       return VAR_ERR_OUT_OF_MEMORY;
   }
   Dmsg2(100, "val=%s len=%d\n", val, p-val);

   v = (char *)malloc(p-val+1);
   memcpy(v, val, p-val);
   v[p-val] = 0;
   *val_ptr = v;
   *val_len = p-val;
   *val_size = p-val+1;
   Dmsg1(100, "v=%s\n", v);
   return VAR_OK;
}
