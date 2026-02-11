TuxReloadWeapon()
{
	if (ItemMap[Me.weapon_item.type].item_gun_ammo_clip_size == Me.weapon_item.ammo_clip)
		return;

	if (Me.paralyze_duration)
		return;

	if (Me.weapon_item.type == -1)
		return;

	const char *ammo_type = ammo_desc_for_weapon(Me.weapon_item.type);

	int count = CountItemtypeInInventory(GetItemIndexByName(ammo_type));
	if (count > ItemMap[Me.weapon_item.type].item_gun_ammo_clip_size - Me.weapon_item.ammo_clip)
		count = ItemMap[Me.weapon_item.type].item_gun_ammo_clip_size - Me.weapon_item.ammo_clip;

	if (!count)
	{
		No_Ammo_Sound();
		No_Ammo_Sound();
		append_new_game_message(_("Out of \4%s\5!"), ammo_type);
		return;
	}
	int i;
	for (i = 0; i < count; i++)
		DeleteOneInventoryItemsOfType(GetItemIndexByName(ammo_type));
	Me.weapon_item.ammo_clip += count;
	Me.busy_time = ItemMap[Me.weapon_item.type].item_gun_reloading_time;
	Me.busy_time *= RangedRechargeMultiplierTable[Me.ranged_weapon_skill];
	Me.busy_type = WEAPON_RELOAD;
}
