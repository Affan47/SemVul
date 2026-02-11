mapif_parse_GuildEmblem(int fd,int len,int guild_id,int dummy,const char *data)
{
	const struct guild *g1 = guilddb_load_num(guild_id);
	struct guild g2;

	if(g1 == NULL)
		return 0;
	memcpy(&g2,g1,sizeof(struct guild));
	memcpy(g2.emblem_data,data,len);
	g2.emblem_len=len;
	g2.emblem_id++;
	guilddb_save(&g2);
	return mapif_guild_emblem(&g2);
}
