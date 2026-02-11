fileset_handler(void *ctx, int num_fields, char **row)
{

   if (row[0]) {
      add_prompt((UAContext *)ctx, row[0]);
   }
   return 0;
}
