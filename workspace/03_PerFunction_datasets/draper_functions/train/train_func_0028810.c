_match_list_del(Eina_List **list,
                Match_Config *m)
{
   Eina_List *l;

   l = eina_list_data_find_list(*list, m);
   if (!l) return;
   *list = eina_list_remove_list(*list, l);
   _match_free(m);
}
