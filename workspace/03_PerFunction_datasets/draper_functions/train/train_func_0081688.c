tds8_read_table_names(TDSSOCKET *tds, int remainder, struct namelist **p_head)
{
	struct namelist *head = NULL, *cur = NULL, *prev;
	int num_names = 0;


	while (remainder > 0) {
		int namelen, elements, i, len;
		char *partials[4], *p;

		prev = cur;
		if (!(cur = (struct namelist *) malloc(sizeof(struct namelist)))) {
			tds_free_namelist(head);
			return -1;
		}

		cur->name = NULL;
		cur->next = NULL;
		if (prev)
			prev->next = cur;
		else
			head = cur;

		elements = tds_get_byte(tds);
		--remainder;
		if (elements <= 0 || elements > 4) {
			tds_free_namelist(head);
			return -1;
		}


		len = 0;
		for (i = 0; i < elements; ++i) {
			namelen = tds_get_smallint(tds);
			remainder -= 2 + 2 * namelen;
			if (tds_alloc_get_string(tds, &partials[i], namelen) < 0) {
				while (i > 0)
					free(partials[--i]);
				tds_free_namelist(head);
				return -1;
			}
			len += tds_quote_id(tds, NULL, partials[i], -1) + 1;
		}


		p = (char *) malloc(len);
		if (!p) {
			i = elements;
			while (i > 0)
				free(partials[--i]);
			tds_free_namelist(head);
			return -1;
		}


		cur->name = p;
		for (i = 0; i < elements; ++i) {
			p += tds_quote_id(tds, p, partials[i], -1);
			*p++ = '.';
			free(partials[i]);
		}
		*--p = 0;

		num_names++;
	}

	*p_head = head;
	return num_names;
}
