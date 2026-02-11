curse_weapon(void)
{
	object_type *o_ptr;

	char o_name[80];


	o_ptr = &inventory[INVEN_WIELD];


	if (!o_ptr->k_idx) return (FALSE);


	object_desc(o_name, sizeof(o_name), o_ptr, ODESC_FULL);


	if (artifact_p(o_ptr) && (randint0(100) < 50))
	{

		msg_format("A %s tries to %s, but your %s resists the effects!",
		           "terrible black aura", "surround your weapon", o_name);
	}


	else
	{

		msg_format("A terrible black aura blasts your %s!", o_name);


		o_ptr->to_h = 0 - randint1(3);
		o_ptr->to_d = 0 - randint1(3);


		flags_set(o_ptr->flags, OF_SIZE, OF_LIGHT_CURSE, OF_HEAVY_CURSE, FLAG_END);


		p_ptr->update |= (PU_BONUS);


		p_ptr->update |= (PU_MANA);


		p_ptr->redraw |= (PR_INVEN | PR_EQUIP);
	}


	return (TRUE);
}
