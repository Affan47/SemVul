obj_desc_inscrip(const object_type *o_ptr, char *buf, size_t max, size_t end)
{
	const char *u[4] = { 0, 0, 0, 0 };
	int n = 0;
	int feel = object_pseudo(o_ptr);
	bitflag flags_known[OF_SIZE];

	object_flags_known(o_ptr, flags_known);


	if (o_ptr->note)
		u[n++] = quark_str(o_ptr->note);


	if (!object_is_known(o_ptr) && feel)
	{

		if (!object_was_worn(o_ptr) && ego_item_p(o_ptr))
			u[n++] = "ego";
		else
			u[n++] = inscrip_text[feel];
	}
	else if ((o_ptr->ident & IDENT_EMPTY) && !object_is_known(o_ptr))
		u[n++] = "empty";
	else if (!object_is_known(o_ptr) && object_was_worn(o_ptr))
	{
		if (wield_slot(o_ptr) == INVEN_WIELD || wield_slot(o_ptr) == INVEN_BOW)
			u[n++] = "wielded";
		else u[n++] = "worn";
	}
	else if (!object_is_known(o_ptr) && object_was_fired(o_ptr))
		u[n++] = "fired";
	else if (!object_flavor_is_aware(o_ptr) && object_flavor_was_tried(o_ptr))
		u[n++] = "tried";


	if (flags_test(flags_known, OF_SIZE, OF_CURSE_MASK, FLAG_END))
		u[n++] = "cursed";


	if (squelch_item_ok(o_ptr))
		u[n++] = "squelch";

	if (n)
	{
		int i;
		for (i = 0; i < n; i++)
		{
			if (i == 0)
				strnfcat(buf, max, &end, " {");
			strnfcat(buf, max, &end, "%s", u[i]);
			if (i < n-1)
				strnfcat(buf, max, &end, ", ");
		}

		strnfcat(buf, max, &end, "}");
	}

	return end;
}
