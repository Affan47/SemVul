accumulate(uint32_t * const p)
{
	struct top *tp, *tp2;
	const char *q;
	unsigned int u, l;
	uint8_t t;
	int i;


	u = 0;
	q = VSL_DATA(p);
	l = VSL_LEN(p);
	t = VSL_TAG(p);
	for (i = 0; i < l; i++, q++) {
		if (f_flag && (*q == ':' || isspace(*q))) {
			l = q - VSL_DATA(p);
			break;
		}
		u += *q;
	}

	VTAILQ_FOREACH(tp, &top_head, list) {
		if (tp->hash != u)
			continue;
		if (tp->tag != t)
			continue;
		if (tp->clen != l)
			continue;
		if (memcmp(VSL_DATA(p), tp->rec_data, l))
			continue;
		tp->count += 1.0;
		break;
	}
	if (tp == NULL) {
		ntop++;
		tp = calloc(sizeof *tp, 1);
		assert(tp != NULL);
		tp->rec_data = calloc(l + 1, 1);
		assert(tp->rec_data != NULL);
		tp->hash = u;
		tp->count = 1.0;
		tp->clen = l;
		tp->tag = t;
		memcpy(tp->rec_data, VSL_DATA(p), l);
		tp->rec_data[l] = '\0';
		VTAILQ_INSERT_TAIL(&top_head, tp, list);
	}
	while (1) {
		tp2 = VTAILQ_PREV(tp, tophead, list);
		if (tp2 == NULL || tp2->count >= tp->count)
			break;
		VTAILQ_REMOVE(&top_head, tp2, list);
		VTAILQ_INSERT_AFTER(&top_head, tp, tp2, list);
	}
	while (1) {
		tp2 = VTAILQ_NEXT(tp, list);
		if (tp2 == NULL || tp2->count <= tp->count)
			break;
		VTAILQ_REMOVE(&top_head, tp2, list);
		VTAILQ_INSERT_BEFORE(tp, tp2, list);
	}
}
