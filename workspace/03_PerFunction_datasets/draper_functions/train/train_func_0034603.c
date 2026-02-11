submodel_rotate(model_subsystem *psub, submodel_instance_info *sii)
{
	bsp_info * sm;

	if ( psub->subobj_num < 0 ) return;

	polymodel *pm = model_get(psub->model_num);
	sm = &pm->submodel[psub->subobj_num];

	if ( sm->movement_type != MOVEMENT_TYPE_ROT ) return;


	sii->prev_angs = sii->angs;


	float diff = sii->desired_turn_rate - sii->cur_turn_rate;

	float final_turn_rate;
	if (diff > 0) {
		final_turn_rate = sii->cur_turn_rate + sii->turn_accel * flFrametime;
		if (final_turn_rate > sii->desired_turn_rate) {
			final_turn_rate = sii->desired_turn_rate;
		}
	} else if (diff < 0) {
		final_turn_rate = sii->cur_turn_rate - sii->turn_accel * flFrametime;
		if (final_turn_rate < sii->desired_turn_rate) {
			final_turn_rate = sii->desired_turn_rate;
		}
	} else {
		final_turn_rate = sii->desired_turn_rate;
	}

	float delta = (sii->cur_turn_rate + final_turn_rate) * 0.5f * flFrametime;
	sii->cur_turn_rate = final_turn_rate;


	switch( sm->movement_axis )	{
	case MOVEMENT_AXIS_X:
		sii->angs.p += delta;

		while (sii->angs.p > PI2)
			sii->angs.p -= PI2;
		while (sii->angs.p < 0.0f)
			sii->angs.p += PI2;

		break;
	case MOVEMENT_AXIS_Y:
		sii->angs.h += delta;

		while (sii->angs.h > PI2)
			sii->angs.h -= PI2;
		while (sii->angs.h < 0.0f)
			sii->angs.h += PI2;

		break;
	case MOVEMENT_AXIS_Z:
		sii->angs.b += delta;

		while (sii->angs.b > PI2)
			sii->angs.b -= PI2;
		while (sii->angs.b < 0.0f)
			sii->angs.b += PI2;

		break;
	}
}
