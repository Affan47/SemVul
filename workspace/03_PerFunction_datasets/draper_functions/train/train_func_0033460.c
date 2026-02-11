mojo_list_init(void)
{
	struct mojo_list *l = zalloc(sizeof(struct mojo_list));
	TAILQ_INIT(&l->mojo_list_head);

	return l;
}
