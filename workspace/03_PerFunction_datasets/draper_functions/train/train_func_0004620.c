srv_dynamic_maxconn(const struct server *s)
{
	unsigned int max;

	if (s->proxy->beconn >= s->proxy->fullconn)

		max = s->maxconn;
	else if (s->minconn == s->maxconn)

		max = s->maxconn;
	else max = MAX(s->minconn,
		       s->proxy->beconn * s->maxconn / s->proxy->fullconn);

	if ((s->state == SRV_ST_STARTING) &&
	    now.tv_sec < s->last_change + s->slowstart &&
	    now.tv_sec >= s->last_change) {
		unsigned int ratio;
		ratio = 100 * (now.tv_sec - s->last_change) / s->slowstart;
		max = MAX(1, max * ratio / 100);
	}
	return max;
}
