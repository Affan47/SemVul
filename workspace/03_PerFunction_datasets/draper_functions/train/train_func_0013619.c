guild_addcastleinfoevent(int castle_id, int idx, const char *name)
{
	struct eventlist *ev;
	int code;

	if( name==NULL || *name==0 )
		return;

	code = castle_id | (idx << 16);
	ev = (struct eventlist *)aCalloc(1,sizeof(struct eventlist));
	memcpy(ev->name,name,sizeof(ev->name));
	ev->name[sizeof(ev->name)-1] = '\0';
	ev->next = (struct eventlist *)numdb_insert(guild_castleinfoevent_db,code,ev);

	return;
}
