mls_sid_to_context(struct context *context,
			char **scontext)
{
	char *scontextp, *nm;
	int i, l, head, prev;
	struct ebitmap *e;
	struct ebitmap_node *node;

	if (!policydb.mls_enabled)
		return;

	scontextp = *scontext;

	*scontextp = ':';
	scontextp++;

	for (l = 0; l < 2; l++) {
		strcpy(scontextp, sym_name(&policydb, SYM_LEVELS,
					   context->range.level[l].sens - 1));
		scontextp += strlen(scontextp);


		head = -2;
		prev = -2;
		e = &context->range.level[l].cat;
		ebitmap_for_each_positive_bit(e, node, i) {
			if (i - prev > 1) {

				if (prev != head) {
					if (prev - head > 1)
						*scontextp++ = '.';
					else
						*scontextp++ = ',';
					nm = sym_name(&policydb, SYM_CATS, prev);
					strcpy(scontextp, nm);
					scontextp += strlen(nm);
				}
				if (prev < 0)
					*scontextp++ = ':';
				else
					*scontextp++ = ',';
				nm = sym_name(&policydb, SYM_CATS, i);
				strcpy(scontextp, nm);
				scontextp += strlen(nm);
				head = i;
			}
			prev = i;
		}

		if (prev != head) {
			if (prev - head > 1)
				*scontextp++ = '.';
			else
				*scontextp++ = ',';
			nm = sym_name(&policydb, SYM_CATS, prev);
			strcpy(scontextp, nm);
			scontextp += strlen(nm);
		}

		if (l == 0) {
			if (mls_level_eq(&context->range.level[0],
					 &context->range.level[1]))
				break;
			else
				*scontextp++ = '-';
		}
	}

	*scontext = scontextp;
	return;
}
