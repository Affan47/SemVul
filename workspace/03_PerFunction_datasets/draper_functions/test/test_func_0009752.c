breakpoint_new()
{
	struct breakpoint *b = (struct breakpoint *)ckalloc(sizeof(struct breakpoint));
	if (break_base) break_base->previous = b;
	b->next = break_base;
	b->previous = 0;
	b->id = breakpoint_max_id++;
	b->file = 0;
	b->line = NO_LINE;
	b->pat = 0;
	b->re = 0;
	b->expr = 0;
	b->cmd = 0;
	break_base = b;
	return(b);
}
