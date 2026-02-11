do_cmd_retrieve(cmd_code code, cmd_arg args[])
{
	int item = args[0].item;
	int amt = args[1].number;

	object_type *o_ptr;
	object_type picked_item;
	char o_name[80];
	int item_new;

	struct store *store = current_store();

	if (store->sidx != STORE_HOME) {
		msg("You are not currently at home.");
		return;
	}


	o_ptr = &store->stock[item];


	object_copy_amt(&picked_item, o_ptr, amt);


	if (!inven_carry_okay(&picked_item))
	{
		msg("You cannot carry that many items.");
		return;
	}


	distribute_charges(o_ptr, &picked_item, amt);


	item_new = inven_carry(p_ptr, &picked_item);


	object_desc(o_name, sizeof(o_name), &p_ptr->inventory[item_new],
				ODESC_PREFIX | ODESC_FULL);


	msg("You have %s (%c).", o_name, index_to_label(item_new));


	handle_stuff(p_ptr);


	store_item_increase(store, item, -amt);
	store_item_optimize(store, item);

	event_signal(EVENT_INVENTORY);
	event_signal(EVENT_EQUIPMENT);
}
