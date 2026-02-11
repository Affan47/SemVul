ast_config_sort_categories(struct ast_config *config, int descending,
								int (*comparator)(struct ast_category *p, struct ast_category *q))
{


	int insize = 1;
	struct ast_category *p, *q, *e, *tail;
	int nmerges, psize, qsize, i;


	if (descending) {
		descending = -1;
	} else {
		descending = 1;
	}

	if (!config->root) {
		return;
	}

	while (1) {
		p = config->root;
		config->root = NULL;
		tail = NULL;

		nmerges = 0;

		while (p) {
			nmerges++;


			q = p;
			psize = 0;
			for (i = 0; i < insize; i++) {
				psize++;
				q = q->next;
				if (!q) {
					break;
				}
			}


			qsize = insize;


			while (psize > 0 || (qsize > 0 && q)) {

				if (psize == 0) {

					e = q;
					q = q->next;
					qsize--;
				} else if (qsize == 0 || !q) {

					e = p; p = p->next; psize--;
				} else if ((comparator(p,q) * descending) <= 0) {

					e = p;
					p = p->next;
					psize--;
				} else {

					e = q;
					q = q->next;
					qsize--;
				}


				if (tail) {
					tail->next = e;
				} else {
					config->root = e;
				}
				tail = e;
			}


			p = q;
		}

		tail->next = NULL;


		if (nmerges <= 1) {
			return;
		}


		insize *= 2;
	}

}
