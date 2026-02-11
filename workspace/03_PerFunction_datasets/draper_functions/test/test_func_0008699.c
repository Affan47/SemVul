conn_del(conn_t *target)
{
	conn_t	*tmp, *last = NULL;

	tmp = connhead;

	while (tmp) {
		if (tmp == target) {

			if (last)
				last->next = tmp->next;
			else
				connhead = tmp->next;

			pconf_finish(&tmp->ctx);

			free(tmp);
			return;
		}

		last = tmp;
		tmp = tmp->next;
	}

	upslogx(LOG_ERR, "Tried to delete a bogus state connection");
}
