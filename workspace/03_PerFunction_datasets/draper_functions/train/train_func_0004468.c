textui_cmd_fire(void)
{
	object_type *j_ptr, *o_ptr;
	int item;
	int dir;
	cptr q = "Fire which item? ";
	cptr s = "You have nothing to fire.";


	j_ptr = &inventory[INVEN_BOW];


	if (!j_ptr->tval || !p_ptr->state.ammo_tval)
	{
		msg_print("You have nothing to fire with.");
		return;
	}


	item_tester_tval = p_ptr->state.ammo_tval;
	p_ptr->command_wrk = USE_EQUIP;


	if (!get_item(&item, q, s, (USE_INVEN | USE_EQUIP | USE_FLOOR))) return;


	o_ptr = object_from_item_idx(item);


	if (!get_aim_dir(&dir)) return;

	cmd_insert(CMD_FIRE, item, dir);
}
