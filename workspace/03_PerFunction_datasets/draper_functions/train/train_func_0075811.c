buy_item(item *BuyItem, int amount)
{
	float item_price;
	item new_item;

	if (amount <= 0) {
		return -1;
	}

	CopyItem(BuyItem, &new_item);

	if (BuyItem->multiplicity < amount)
		amount = BuyItem->multiplicity;

	new_item.multiplicity = amount;
	item_price = calculate_item_buy_price(&new_item) * new_item.multiplicity;


	if (item_price > Me.Gold) {
		alert_window("%s\n\n%s", ItemMap[BuyItem->type].item_name, _("You can not afford this item."));
		return -1;
	}


	Me.Gold -= item_price;
	give_item(&new_item);
	play_sound("effects/Shop_ItemBoughtSound_0.ogg");


	if(BuyItem->multiplicity == amount) {
		return 1;
	} else {
		BuyItem->multiplicity -= amount;
	}

	return 0;

}
