cap_ls(struct Client *source_p, const char *arg)
{
	if(!IsRegistered(source_p))
		source_p->flags |= FLAGS_CLICAP;


	clicap_generate(source_p, "LS", 0, 0);
}
