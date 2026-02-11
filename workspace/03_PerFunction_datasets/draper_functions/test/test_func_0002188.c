mc_maclist_init (void)
{
	list_others = mc_maclist_read_from_file(LISTDIR "/OUI.list");
	list_wireless = mc_maclist_read_from_file(LISTDIR "/wireless.list");

	return (list_others && list_wireless)? 0 : -1;
}
