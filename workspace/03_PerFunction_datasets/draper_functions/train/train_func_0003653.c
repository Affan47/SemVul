pc_checkskill2(struct map_session_data *sd,int skill_id)
{
	if(sd == NULL)
		return 0;

	if(skill_id >= GUILD_SKILLID) {
		struct guild *g;
		if(sd->status.guild_id > 0 && (g = guild_search(sd->status.guild_id)) != NULL)
			return guild_checkskill(g,skill_id);
		return 0;
	}

	if(skill_id < 0 || skill_id >= MAX_PCSKILL)
		return 0;

	if(sd->status.skill[skill_id].id == skill_id)
		return sd->status.skill[skill_id].lv;

	return 0;
}
