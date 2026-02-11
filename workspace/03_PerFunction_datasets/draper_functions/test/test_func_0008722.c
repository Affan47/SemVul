set_addon_item(item *it, int index)
{


	if (ui.custom_item.upgrade_sockets.size <= index ||
	       ui.addon_items[index].type != -1 ||
	       !item_can_be_installed_to_socket(&ui.custom_item, it, index)) {
		return FALSE;
	}


	play_item_sound(it->type, &Me.pos);
	MoveItem(it, &ui.addon_items[index]);


	calculate_cost_and_bonuses();

	return TRUE;
}
