get_equipped_item_in_slot_for(int item_type)
{
	item *equipped_item;
	itemspec *spec;

	spec = &ItemMap[item_type];

	if (spec->item_can_be_installed_in_weapon_slot) {
		equipped_item = &Me.weapon_item;
	}
	else if (spec->item_can_be_installed_in_drive_slot) {
		equipped_item = &Me.drive_item;
	}
	else if (spec->item_can_be_installed_in_armour_slot) {
		equipped_item = &Me.armour_item;
	}
	else if (spec->item_can_be_installed_in_shield_slot) {
		equipped_item = &Me.shield_item;
	}
	else if (spec->item_can_be_installed_in_special_slot) {
		equipped_item = &Me.special_item;
	}
	else
	{
		equipped_item = NULL;
	}

	return equipped_item;
}
