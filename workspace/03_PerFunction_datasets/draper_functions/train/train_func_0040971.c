at_apply(FormStack *st, Fixed space, u32 *group_idx, u32 count)
{
	Fixed max_y;
	u32 i, start;
	GF_Rect *rc;

	start = 0;
	max_y = form_get_group(st, group_idx[0])->final.y;
	if(space>-FIX_ONE) {
		start = 1;
		max_y -= space;
	} else {
		for (i=1; i<count; i++) {
			rc = &form_get_group(st, group_idx[i])->final;
			if (group_idx[i]==0) {
				max_y = rc->y;
				break;
			}
			if (rc->y > max_y) max_y = rc->y;
		}
	}

	for (i=start; i<count; i++) {
		if(group_idx[i] == 0) continue;
		form_get_group(st, group_idx[i])->final.y = max_y;
		fg_update_bounds(form_get_group(st, group_idx[i]));
	}
}
