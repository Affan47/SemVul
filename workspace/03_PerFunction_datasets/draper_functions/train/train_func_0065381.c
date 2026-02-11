generate_base_implied_equalities_const(PlannerInfo *root,
									   EquivalenceClass *ec)
{
	EquivalenceMember *const_em = NULL;
	ListCell   *lc;


	if (list_length(ec->ec_members) == 2 &&
		list_length(ec->ec_sources) == 1)
	{
		RestrictInfo *restrictinfo = (RestrictInfo *) linitial(ec->ec_sources);

		if (bms_membership(restrictinfo->required_relids) != BMS_MULTIPLE)
		{
			distribute_restrictinfo_to_rels(root, restrictinfo);
			return;
		}
	}


	foreach(lc, ec->ec_members)
	{
		EquivalenceMember *cur_em = (EquivalenceMember *) lfirst(lc);

		if (cur_em->em_is_const)
		{
			const_em = cur_em;
			break;
		}
	}
	Assert(const_em != NULL);


	foreach(lc, ec->ec_members)
	{
		EquivalenceMember *cur_em = (EquivalenceMember *) lfirst(lc);
		Oid			eq_op;

		Assert(!cur_em->em_is_child);
		if (cur_em == const_em)
			continue;
		eq_op = select_equality_operator(ec,
										 cur_em->em_datatype,
										 const_em->em_datatype);
		if (!OidIsValid(eq_op))
		{

			ec->ec_broken = true;
			break;
		}
		process_implied_equality(root, eq_op,
								 cur_em->em_expr, const_em->em_expr,
								 ec->ec_relids,
								 ec->ec_below_outer_join,
								 cur_em->em_is_const);
	}
}
