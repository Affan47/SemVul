libmail_mimestack_pop(struct mimestack **p)
{
	struct mimestack *pp= *p;

	if (pp)
	{
		*p=pp->next;
		free(pp->boundary);
		free(pp);
	}
}
