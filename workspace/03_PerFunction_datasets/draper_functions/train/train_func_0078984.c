begin_drag_move_meas(struct inst *inst, int i)
{
	const struct meas *meas = &inst->obj->u.meas;
	struct coord a, b;

	switch (meas->type) {
	case mt_xy_next:
	case mt_xy_max:
		meas_dsc = &meas_dsc_xy;
		break;
	case mt_x_next:
	case mt_x_max:
		meas_dsc = &meas_dsc_x;
		break;
	case mt_y_next:
	case mt_y_max:
		meas_dsc = &meas_dsc_y;
		break;
	default:
		abort();
	}
	highlight = meas_highlight_b;


	a = inst->base;
	b = inst->u.meas.end;
	if (inst->obj->u.meas.inverted)
		SWAP(a, b);
	switch (i) {
	case 0:
		mode = meas->type < 3 ? next_to_min : max_to_min;
		meas_inst = vec_at(inst->obj->u.meas.high, b);
		break;
	case 1:
		mode = min_to_next_or_max;
		meas_inst = vec_at(inst->obj->base, a);
		break;
	default:
		abort();
	}

}
