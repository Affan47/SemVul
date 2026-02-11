storage_guild_delete(int guild_id)
{
	struct guild_storage *gstor = (struct guild_storage *)numdb_erase(guild_storage_db,guild_id);

	if(gstor)
		aFree(gstor);

	return;
}
