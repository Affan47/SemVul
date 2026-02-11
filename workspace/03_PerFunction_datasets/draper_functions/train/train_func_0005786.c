fix_append_rel_relids(List *append_rel_list, int varno, Relids subrelids)
{
	ListCell   *l;
	int			subvarno = -1;


	foreach(l, append_rel_list)
	{
		AppendRelInfo *appinfo = (AppendRelInfo *) lfirst(l);


		Assert(appinfo->parent_relid != varno);

		if (appinfo->child_relid == varno)
		{
			if (subvarno < 0)
				subvarno = bms_singleton_member(subrelids);
			appinfo->child_relid = subvarno;
		}


		substitute_multiple_relids((Node *) appinfo->translated_vars,
								   varno, subrelids);
	}
}
