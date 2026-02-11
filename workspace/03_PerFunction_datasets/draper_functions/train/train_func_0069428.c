sumTotalStats()
{
	globuser *s;
	int i;

	general.from_cnt = 0;
	general.to_cnt = 0;
	general.from_byte = 0;

	for (i = 0 ; i < MAXUSERS; i++)
		for (s = globusers[i]; s != NULL; s = s->next) {
			general.from_cnt += s->u->from_cnt;
			general.to_cnt += s->u->to_cnt;
			general.from_byte += s->u->from_byte;
		}
}
