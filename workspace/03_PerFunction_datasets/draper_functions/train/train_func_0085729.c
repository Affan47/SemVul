calculate_item_buy_price(item * BuyItem)
{
	int i;
	int price = ItemMap[BuyItem->type].base_list_price;


	for (i = 0; i < BuyItem->upgrade_sockets.size; i++) {
		const char *addon = BuyItem->upgrade_sockets.arr[i].addon;
		if (addon) {
			int type = GetItemIndexByName(addon);
			price += ItemMap[type].base_list_price;
		}
	}

	return price;
}
