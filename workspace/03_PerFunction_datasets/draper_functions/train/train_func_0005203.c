free_name_list(NAME_LIST *name_list)
{
   for (int i=0; i < name_list->num_ids; i++) {
      free(name_list->name[i]);
   }
   name_list->num_ids = 0;
}
