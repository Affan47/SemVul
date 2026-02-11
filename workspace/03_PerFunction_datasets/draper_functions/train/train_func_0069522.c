sort_mergesort(mu_pack *const pack, const unsigned char *const order)
{
	const mu_ent	*p,
			*q,
			*m,
			*head = pack->head;
	mu_ent		*tail;

	unsigned long	packsize,
			ssmsize,
			count,
			psize,
			qsize;

	packsize = pack->dirnb + pack->filenb;


	for (ssmsize = 1; ssmsize <= packsize; ssmsize *= 2) {

		q = p = head;


		head = tail = NULL;


		count = packsize;

		while (count) {

			for (psize=0; (psize < ssmsize) && q; psize++)
				q = q->next;


			qsize = ssmsize;


			while (psize || (qsize && q)) {
				if (!psize) {

					m = q;
					q = q->next;
					qsize--;
				} else if (!qsize || !q) {

					m = p;
					p = p->next;
					psize--;
				} else if (inf_global(p, q, order) <= 0) {


					m = p;
					p = p->next;
					psize--;
				} else {

					m = q;
					q = q->next;
					qsize--;
				}


				if (likely(tail))
					tail->next = m;
				else
					head = m;


				tail = (mu_ent *)m;


				count--;
			}


			p = q;
		}


		tail->next = NULL;
	}


	pack->head = head;


	if (pack->filenb) {
		for (p = pack->head; p->filetype < 0; p = p->next);
		pack->fhead = p;
	}

	return;
}
