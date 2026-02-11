qhvec_add(query_hashvec_t *qhvec, const char *word, enum query_hsrc src)
{
	struct query_hash *qh = NULL;

	if G_UNLIKELY(qhvec->count >= qhvec->size)
		return;


	switch (src) {
	case QUERY_H_URN:
		qhvec->has_urn = TRUE;
		if (qhvec->count)
			memmove(&qhvec->vec[1], &qhvec->vec[0],
				qhvec->count * sizeof(qhvec->vec[0]));
		qh = &qhvec->vec[0];
		break;
	case QUERY_H_WORD:
		qh = &qhvec->vec[qhvec->count];
		break;
	}

	g_assert(qh != NULL);

	qhvec->count++;
	qh->hashcode = qrp_hashcode(word);
	qh->source = src;
}
