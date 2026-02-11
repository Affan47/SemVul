mc_maclist_print_from_list (card_mac_list_item_t *list, const char *keyword)
{
	   int i = 0;

	   while (list[i].name) {
		   if (!keyword || (keyword && strstr(list[i].name, keyword))) {
			 printf ("%04i - %02x:%02x:%02x - %s\n", i,
				    list[i].byte[0], list[i].byte[1],list[i].byte[2],
				    list[i].name);
		   }
			 i++;
	   }
}
