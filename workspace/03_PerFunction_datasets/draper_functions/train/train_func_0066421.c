do_cmd_knowledge_ego_items(const char *name, int row)
{
	group_funcs obj_f =
		{TV_GOLD, FALSE, ego_grp_name, e_cmp_tval, default_group, 0};

	member_funcs ego_f = {display_ego_item, desc_ego_fake, 0, 0, recall_prompt, 0, 0};

	int *egoitems;
	int e_count = 0;
	int i, j;


	egoitems = C_ZNEW(z_info->e_max * EGO_TVALS_MAX, int);
	default_join = C_ZNEW(z_info->e_max * EGO_TVALS_MAX, join_t);

	for (i = 0; i < z_info->e_max; i++)
	{
		if (e_info[i].everseen || OPT(cheat_xtra))
		{
			for (j = 0; j < EGO_TVALS_MAX && e_info[i].tval[j]; j++)
			{
				int gid = obj_group_order[e_info[i].tval[j]];


				if (j > 0 && gid == default_join[e_count - 1].gid) continue;

				egoitems[e_count] = e_count;
				default_join[e_count].oid = i;
				default_join[e_count++].gid = gid;
			}
		}
	}

	display_knowledge("ego items", egoitems, e_count, obj_f, ego_f, NULL);

	FREE(default_join);
	FREE(egoitems);
}
