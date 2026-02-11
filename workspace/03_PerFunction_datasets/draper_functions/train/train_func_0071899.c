buildin_getmapmobs_sub(struct block_list *bl,va_list ap)
{
	struct mob_data *md;
	char *event = va_arg(ap,char *);

	nullpo_retr(0, bl);
	nullpo_retr(0, md = (struct mob_data *)bl);

	if(md->hp > 0 && (!event || strcmp(event,md->npc_event) == 0))
		return 1;
	return 0;
}
