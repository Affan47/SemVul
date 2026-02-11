jp_free_DB_records(GList **br_list)
{
   GList *temp_list;
   buf_rec *br;

   for (temp_list = *br_list; temp_list; temp_list = temp_list->next) {
      if (temp_list->data) {
         br=temp_list->data;
         if (br->buf) {
            free(br->buf);
            temp_list->data=NULL;
         }
         free(br);
      }
   }
   g_list_free(*br_list);
   *br_list=NULL;

   return EXIT_SUCCESS;
}
