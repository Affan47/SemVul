arp_spoof_del_item(void)
{
	int i;
	struct arp_spoof_info *asi;

	arp_spoof_list_items();
	i = menu_choose_unr("item nr. to delete", 0, arp_spoof_count() - 1, -1);
	if (i >= 0) {
		asi = list_at(&l_arp_spoof, i);
		stop_arp_spoof(asi);

	}
}
