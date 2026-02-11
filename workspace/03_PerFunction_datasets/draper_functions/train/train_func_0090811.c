svin_apply(FormStack *st, u32 *group_idx, u32 count)
{
	u32 i, len;
	Fixed tot_len, inter_space;
	tot_len = 0;
	inter_space = st->clip.height;
	len = 0;
	for (i=0; i<count;i++) {
		if (group_idx[i] != 0) {
			tot_len += form_get_group(st, group_idx[i])->final.height;
			len++;
		}
	}
	inter_space -= tot_len;
	inter_space /= (len+1);

	for (i=0; i<count; i++) {
		if (group_idx[i] == 0) continue;
		if (!i) {
			form_get_group(st, group_idx[0])->final.y = st->clip.y - inter_space;
		} else {
			form_get_group(st, group_idx[i])->final.y =
				form_get_group(st, group_idx[i-1])->final.y - form_get_group(st, group_idx[i-1])->final.height -
				inter_space;
		}
		fg_update_bounds(form_get_group(st, group_idx[i]));
	}
}
