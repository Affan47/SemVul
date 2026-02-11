mobskill_use_pos( struct mob_data *md, int skill_x, int skill_y, int skill_idx)
{
	struct mob_skill *mds, *ms;
	int i, casttime;
	unsigned int tick = gettick();

	nullpo_retr(0, md);

	mds = mob_db[md->class_].skill;
	ms  = &mds[skill_idx];

	casttime     = ms->casttime;
	md->skillidx = skill_idx;

	for(i=0; i<mob_db[md->class_].maxskill; i++) {
		if(mds[i].skill_id == ms->skill_id)
			md->skilldelay[i] = tick + casttime;
	}

	return unit_skilluse_pos2(&md->bl, skill_x, skill_y, ms->skill_id, ms->skill_lv, casttime, ms->cancel);
}
