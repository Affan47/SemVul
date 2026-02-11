squelch_item_ok(const object_type *o_ptr)
{
	object_kind *k_ptr = &k_info[o_ptr->k_idx];
	byte type;


	if (artifact_p(o_ptr))
		return FALSE;


	if (check_for_inscrip(o_ptr, "!k") || check_for_inscrip(o_ptr, "!*"))
		return FALSE;


	if (o_ptr->tval == TV_CHEST && o_ptr->pval == 0)
		return TRUE;


	if (OPT(squelch_worthless) && o_ptr->tval != TV_GOLD)
	{
		if (object_flavor_is_aware(o_ptr) && k_ptr->cost == 0)
			return TRUE;
		if (object_is_known_cursed(o_ptr))
			return TRUE;
	}


	if (object_flavor_is_aware(o_ptr) ?
		 kind_is_squelched_aware(k_ptr) :
		 kind_is_squelched_unaware(k_ptr))
		return TRUE;

	type = squelch_type_of(o_ptr);
	if (type == TYPE_MAX)
		return FALSE;


	if (object_is_known_not_artifact(o_ptr) && squelch_level[type] == SQUELCH_ALL)
		return TRUE;


	if (squelch_level_of(o_ptr) <= squelch_level[type])
		return TRUE;
	else
		return FALSE;
}
