handle_encap(struct Client *client_p, struct Client *source_p,
	     const char *command, int parc, const char *parv[])
{
	struct Message *mptr;
	struct MessageEntry ehandler;
	MessageHandler handler = 0;

	parv[0] = source_p->name;

	mptr = hash_parse(command);

	if(mptr == NULL || mptr->cmd == NULL)
		return;

	ehandler = mptr->handlers[ENCAP_HANDLER];
	handler = ehandler.handler;

	if(parc < ehandler.min_para ||
	   (ehandler.min_para && EmptyString(parv[ehandler.min_para - 1])))
		return;

	(*handler) (client_p, source_p, parc, parv);
}
