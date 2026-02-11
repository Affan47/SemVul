db_list_handler(void *ctx, int num_fields, char **row)
{
   db_list_ctx *lctx = (db_list_ctx *)ctx;
   if (num_fields == 1 && row[0]) {
      lctx->add(row[0]);
   }
   return 0;
}
