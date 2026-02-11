_st_store_list(void *data __UNUSED__, Elm_Store_Item_Info *item_info)
{
   Elm_Store_Item_Info_Filesystem *info = (Elm_Store_Item_Info_Filesystem *)item_info;
   int id;
   char sort_id[7];


   char *file = strrchr(info->path, '/');
   if (file) file++;
   else file = info->path;
   id = atoi(file);
   sort_id[0] = ((id >> 30) & 0x3f) + 32;
   sort_id[1] = ((id >> 24) & 0x3f) + 32;
   sort_id[2] = ((id >> 18) & 0x3f) + 32;
   sort_id[3] = ((id >> 12) & 0x3f) + 32;
   sort_id[4] = ((id >>  6) & 0x3f) + 32;
   sort_id[5] = ((id >>  0) & 0x3f) + 32;
   sort_id[6] = 0;
   info->base.sort_id = strdup(sort_id);


   info->base.item_class = itc1;
   info->base.mapping = it1_mapping;
   info->base.data = NULL;
   return EINA_TRUE;
}
