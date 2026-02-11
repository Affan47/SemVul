object_check_for_ident(object_type *o_ptr)
{
	bitflag flags[OF_SIZE], known_flags[OF_SIZE];

	object_flags(o_ptr, flags);
	object_flags_known(o_ptr, known_flags);


	flags_clear(flags, OF_SIZE, OF_OBJ_ONLY_MASK, FLAG_END);
	flags_clear(known_flags, OF_SIZE, OF_OBJ_ONLY_MASK, FLAG_END);

	if (!of_is_equal(flags, known_flags)) return FALSE;


	if ((object_attack_plusses_are_visible(o_ptr) || (object_was_sensed(o_ptr) && o_ptr->to_h == 0 && o_ptr->to_d == 0)) &&
	    (object_defence_plusses_are_visible(o_ptr) || (object_was_sensed(o_ptr) && o_ptr->to_a == 0)) &&
	    (object_effect_is_known(o_ptr) || !object_effect(o_ptr)))
	{
		object_notice_everything(o_ptr);
		return TRUE;
	}


	else if (ego_item_p(o_ptr))
	{

		if (object_was_worn(o_ptr))
			object_notice_ego(o_ptr);
	}

	return FALSE;
}
