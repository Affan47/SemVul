env_export(unsigned char *var)
{
	struct env_lst *ep;

	if ((ep = env_find(var)))
		ep->export = 1;
}
