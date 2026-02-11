gf_dash_group_get_num_segments_ready(GF_DashClient *dash, u32 idx, Bool *group_is_done)
{
	u32 res = 0;
	GF_DASH_Group *group;

	gf_mx_p(dash->dl_mutex);
	group = gf_list_get(dash->groups, idx);

	*group_is_done = 0;
	if (!group) {
		*group_is_done = 1;
	} else {
		*group_is_done = group->done;
		res = group->nb_cached_segments;
	}
	gf_mx_v(dash->dl_mutex);
	return res;
}
