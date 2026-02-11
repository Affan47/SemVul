transfer(struct name *to, struct name *mailargs, FILE *input, struct header *hp)
{
	char	o[LINESIZE], *cp;
	struct name	*np, *nt;
	int	cnt = 0;
	FILE	*ef;
	enum okay	ok = OKAY;

	np = to;
	while (np) {
		snprintf(o, sizeof o, "smime-encrypt-%s", np->n_name);
		if ((cp = value(o)) != NULL) {
			if ((ef = smime_encrypt(input, cp, np->n_name)) != 0) {
				nt = nalloc(np->n_name,
					np->n_type & ~(GFULL|GSKIN));
				if (start_mta(nt, mailargs, ef, hp) != OKAY)
					ok = STOP;
				Fclose(ef);
			} else {
				fprintf(stderr, "Message not sent to <%s>\n",
						np->n_name);
				senderr++;
			}
			rewind(input);
			if (np->n_flink)
				np->n_flink->n_blink = np->n_blink;
			if (np->n_blink)
				np->n_blink->n_flink = np->n_flink;
			if (np == to)
				to = np->n_flink;
			np = np->n_flink;
		} else {
			cnt++;
			np = np->n_flink;
		}
	}
	if (cnt) {
		if (value("smime-force-encryption") ||
				start_mta(to, mailargs, input, hp) != OKAY)
			ok = STOP;
	}
	return ok;
}
