define_fs_use(int behavior)
{
	ocontext_t *newc, *c, *head;

	if (policydbp->target_platform != SEPOL_TARGET_SELINUX) {
		yyerror("fsuse not supported for target");
		return -1;
	}

	if (pass == 1) {
		free(queue_remove(id_queue));
		parse_security_context(NULL);
		return 0;
	}

	newc = (ocontext_t *) malloc(sizeof(ocontext_t));
	if (!newc) {
		yyerror("out of memory");
		return -1;
	}
	memset(newc, 0, sizeof(ocontext_t));

	newc->u.name = (char *)queue_remove(id_queue);
	if (!newc->u.name) {
		free(newc);
		return -1;
	}
	newc->v.behavior = behavior;
	if (parse_security_context(&newc->context[0])) {
		free(newc->u.name);
		free(newc);
		return -1;
	}

	head = policydbp->ocontexts[OCON_FSUSE];

	for (c = head; c; c = c->next) {
		if (!strcmp(newc->u.name, c->u.name)) {
			yyerror2("duplicate fs_use entry for filesystem type %s",
				 newc->u.name);
			context_destroy(&newc->context[0]);
			free(newc->u.name);
			free(newc);
			return -1;
		}
	}

	newc->next = head;
	policydbp->ocontexts[OCON_FSUSE] = newc;
	return 0;
}
