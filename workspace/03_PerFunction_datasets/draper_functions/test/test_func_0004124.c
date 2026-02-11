server_warmup(struct task *t)
{
	struct server *s = t->context;


	t->expire = TICK_ETERNITY;
	if ((s->admin & SRV_ADMF_MAINT) ||
	    (s->state != SRV_ST_STARTING))
		return t;


	server_recalc_eweight(s);


	pendconn_grab_from_px(s);


	if (s->state == SRV_ST_STARTING)
		t->expire = tick_add(now_ms, MS_TO_TICKS(MAX(1000, s->slowstart / 20)));
	return t;
}
