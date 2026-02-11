growjobtab(void)
{
	size_t len;
	ptrdiff_t offset;
	struct job *jp, *jq;

	len = njobs * sizeof(*jp);
	jq = jobtab;
	jp = ckrealloc(jq, len + 4 * sizeof(*jp));

	offset = (char *)jp - (char *)jq;
	if (offset) {

		size_t l = len;

		jq = (struct job *)((char *)jq + l);
		while (l) {
			l -= sizeof(*jp);
			jq--;
#define joff(p) ((struct job *)((char *)(p) + l))
#define jmove(p) (p) = (void *)((char *)(p) + offset)
			if (likely(joff(jp)->ps == &jq->ps0))
				jmove(joff(jp)->ps);
			if (joff(jp)->prev_job)
				jmove(joff(jp)->prev_job);
		}
		if (curjob)
			jmove(curjob);
#undef joff
#undef jmove
	}

	njobs += 4;
	jobtab = jp;
	jp = (struct job *)((char *)jp + len);
	jq = jp + 3;
	do {
		jq->used = 0;
	} while (--jq >= jp);
	return jp;
}
