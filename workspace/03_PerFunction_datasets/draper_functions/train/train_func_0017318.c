guild2storage(int guild_id)
{
	struct guild_storage *gs = NULL;

	if(guild_search(guild_id) != NULL) {
		gs = (struct guild_storage *)numdb_search(guild_storage_db,guild_id);
		if(gs == NULL) {
			gs = (struct guild_storage *)aCalloc(1,sizeof(struct guild_storage));
			gs->guild_id = guild_id;
			numdb_insert(guild_storage_db,gs->guild_id,gs);
		}
	}

	return gs;
}
