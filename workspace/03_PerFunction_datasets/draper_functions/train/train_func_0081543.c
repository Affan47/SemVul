new_auth(void) {
	struct auth_s *tmp;

	tmp = (struct auth_s *)malloc(sizeof(struct auth_s));
	if (tmp == NULL)
		return NULL;

	memset(tmp->user, 0, MINIBUF_SIZE);
	memset(tmp->domain, 0, MINIBUF_SIZE);
	memset(tmp->workstation, 0, MINIBUF_SIZE);
	memset(tmp->passntlm2, 0, MINIBUF_SIZE);
	memset(tmp->passnt, 0, MINIBUF_SIZE);
	memset(tmp->passlm, 0, MINIBUF_SIZE);
	tmp->hashntlm2 = 1;
	tmp->hashnt = 0;
	tmp->hashlm = 0;
	tmp->flags = 0;

	return tmp;
}
