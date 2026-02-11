do_autopickup(void)
{
	int py = p_ptr->py;
	int px = p_ptr->px;

	s16b this_o_idx, next_o_idx = 0;

	object_type *o_ptr;


	byte objs_picked_up = 0;

	size_t floor_num = 0;
	int floor_list[MAX_FLOOR_STACK + 1];


	if (!cave->o_idx[py][px]) return (0);


	py_pickup_gold();


	for (this_o_idx = cave->o_idx[py][px]; this_o_idx; this_o_idx = next_o_idx)
	{

		o_ptr = object_byid(this_o_idx);
		next_o_idx = o_ptr->next_o_idx;


		if (squelch_item_ok(o_ptr) || !o_ptr->kind) continue;


		if (floor_num >= N_ELEMENTS(floor_list)) break;


		disturb(p_ptr, 0, 0);


		if (auto_pickup_okay(o_ptr))
		{

			py_pickup_aux(this_o_idx, TRUE);
			objs_picked_up++;

			continue;
		}


		floor_list[floor_num] = this_o_idx;


		floor_num++;
	}

	return objs_picked_up;
}
