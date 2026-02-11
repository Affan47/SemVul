define_port_context(unsigned int low, unsigned int high)
{
	ocontext_t *newc, *c, *l, *head;
	unsigned int protocol;
	char *id;

#ifdef SEPOL_TARGET_XEN
	if (policydbp->target_platform != SEPOL_TARGET_SELINUX) {
		yyerror("portcon not supported for target");
		return -1;
	}
#endif

	if (pass == 1) {
		id = (char *)queue_remove(id_queue);
		free(id);
		parse_security_context(NULL);
		return 0;
	}

	newc = malloc(sizeof(ocontext_t));
	if (!newc) {
		yyerror("out of memory");
		return -1;
	}
	memset(newc, 0, sizeof(ocontext_t));

	id = (char *)queue_remove(id_queue);
	if (!id) {
		free(newc);
		return -1;
	}
	if ((strcmp(id, "tcp") == 0) || (strcmp(id, "TCP") == 0)) {
		protocol = IPPROTO_TCP;
	} else if ((strcmp(id, "udp") == 0) || (strcmp(id, "UDP") == 0)) {
		protocol = IPPROTO_UDP;
	} else {
		yyerror2("unrecognized protocol %s", id);
		free(newc);
		return -1;
	}

	newc->u.port.protocol = protocol;
	newc->u.port.low_port = low;
	newc->u.port.high_port = high;

	if (low > high) {
		yyerror2("low port %d exceeds high port %d", low, high);
		free(newc);
		return -1;
	}

	if (parse_security_context(&newc->context[0])) {
		free(newc);
		return -1;
	}


	head = policydbp->ocontexts[OCON_PORT];
	for (l = NULL, c = head; c; l = c, c = c->next) {
		unsigned int prot2, low2, high2;

		prot2 = c->u.port.protocol;
		low2 = c->u.port.low_port;
		high2 = c->u.port.high_port;
		if (protocol != prot2)
			continue;
		if (low == low2 && high == high2) {
			yyerror2("duplicate portcon entry for %s %d-%d ", id, low, high);
			goto bad;
		}
		if (low2 <= low && high2 >= high) {
			yyerror2("portcon entry for %s %d-%d hidden by earlier " "entry for %d-%d", id, low, high, low2, high2);
			goto bad;
		}
	}
	free(id);

	if (l)
		l->next = newc;
	else
		policydbp->ocontexts[OCON_PORT] = newc;

	return 0;

      bad:
	free(newc);
	return -1;
}
