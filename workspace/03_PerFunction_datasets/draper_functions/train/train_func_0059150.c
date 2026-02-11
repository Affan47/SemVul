find_event(char *pat, int len)
{
	register HIST * hp;

	for (hp = FIRSTHIST; hp->len; hp = NEXTHIST(hp)) {
		if ((hp->len == len) && (memcmp(hp->data, pat, len) == 0))
			return hp;
	}
	return NULL;
}
