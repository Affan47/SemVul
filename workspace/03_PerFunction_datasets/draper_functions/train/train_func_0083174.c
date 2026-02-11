parse_record (unsigned char *answer,
              unsigned char *p,
              unsigned char *end,
              srvinfo **res)
{
	srvinfo *srv;


	if (p + 8 > end)
		return 0;

	srv = calloc (1, sizeof (srvinfo));
	if (srv == NULL)
		return EAI_MEMORY;

	srv->priority = get_16 (&p, end);
	srv->weight = get_16 (&p, end);
	srv->port = get_16 (&p, end);
	srv->hostname = get_string (answer, end, &p);

	if (!srv->hostname) {
		free (srv);
		return EAI_FAIL;
	}


	while (*res != NULL) {
		if (srv->priority == (*res)->priority) {

			if (!!srv->weight > !!((*res)->weight))
				break;
		} else if (srv->priority > (*res)->priority) {
			break;
		}
		res = &((*res)->next);
	}

	srv->next = *res;
	*res = srv;

	return 0;
}
