sgen_los_count_cards (long long *num_total_cards, long long *num_marked_cards)
{
	LOSObject *obj;
	long long total_cards = 0;
	long long marked_cards = 0;

	for (obj = los_object_list; obj; obj = obj->next) {
		int i;
		guint8 *cards = sgen_card_table_get_card_scan_address ((mword) obj->data);
		guint8 *cards_end = sgen_card_table_get_card_scan_address ((mword) obj->data + sgen_los_object_size (obj) - 1);
		mword num_cards = (cards_end - cards) + 1;

		if (!SGEN_OBJECT_HAS_REFERENCES (obj->data))
			continue;

		total_cards += num_cards;
		for (i = 0; i < num_cards; ++i) {
			if (cards [i])
				++marked_cards;
		}
	}

	*num_total_cards = total_cards;
	*num_marked_cards = marked_cards;
}
