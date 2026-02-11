_grecs_simple_list_create(int dispose)
{
	struct grecs_list *lp = grecs_list_create();
	if (dispose)
		lp->free_entry = listel_dispose;
	return lp;
}
