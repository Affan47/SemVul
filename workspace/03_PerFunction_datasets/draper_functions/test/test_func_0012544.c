join_clause_is_movable_to(RestrictInfo *rinfo, RelOptInfo *baserel)
{

	if (!bms_is_member(baserel->relid, rinfo->clause_relids))
		return false;


	if (bms_is_member(baserel->relid, rinfo->outer_relids))
		return false;


	if (bms_is_member(baserel->relid, rinfo->nullable_relids))
		return false;


	if (bms_overlap(baserel->lateral_referencers, rinfo->clause_relids))
		return false;

	return true;
}
