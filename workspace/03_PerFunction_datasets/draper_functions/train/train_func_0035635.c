unit_skilluse_id(struct block_list *src, int target_id, int skill_num, int skill_lv)
{
	int id = skill_get_skilldb_id(skill_num);

	if( id == 0 )
		return 0;
	if( skill_lv <= 0 || skill_lv > MAX_SKILL_LEVEL )
		return 0;

	return unit_skilluse_id2(
		src, target_id, skill_num, skill_lv,
		skill_castfix(src, skill_num, skill_db[id].cast[skill_lv-1], skill_db[id].fixedcast[skill_lv-1]),
		skill_db[id].castcancel
	);
}
