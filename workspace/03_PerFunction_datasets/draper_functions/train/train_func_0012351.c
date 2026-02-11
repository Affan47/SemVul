do_cmd_refill(cmd_code code, cmd_arg args[])
{
	object_type *j_ptr = &p_ptr->inventory[INVEN_LIGHT];
	bitflag f[OF_SIZE];

	int item = args[0].item;
	object_type *o_ptr = object_from_item_idx(item);

	if (!item_is_available(item, NULL, USE_INVEN | USE_FLOOR))
	{
		msg("You do not have that item to refill with it.");
		return;
	}


	object_flags(j_ptr, f);

	if (j_ptr->tval != TV_LIGHT)
	{
		msg("You are not wielding a light.");
		return;
	}

	else if (of_has(f, OF_NO_FUEL))
	{
		msg("Your light cannot be refilled.");
		return;
	}


	if (j_ptr->sval == SV_LIGHT_LANTERN)
		refill_lamp(j_ptr, o_ptr, item);


	else if (j_ptr->sval == SV_LIGHT_TORCH)
		refuel_torch(j_ptr, o_ptr, item);

	p_ptr->energy_use = 50;
}
