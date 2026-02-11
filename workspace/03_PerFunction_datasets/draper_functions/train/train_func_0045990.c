evas_font_dir_available_list_free(Eina_List *available)
{
   while (available)
     {
	eina_stringshare_del(available->data);
	available = eina_list_remove(available, available->data);
     }
}
