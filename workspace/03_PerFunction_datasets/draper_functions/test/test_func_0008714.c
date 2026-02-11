STV_MkObject(struct sess *sp, void *ptr, unsigned ltot,
    const struct stv_objsecrets *soc)
{
	struct object *o;
	unsigned l;

	CHECK_OBJ_NOTNULL(soc, STV_OBJ_SECRETES_MAGIC);

	assert(PAOK(ptr));
	assert(PAOK(soc->wsl));
	assert(PAOK(soc->lhttp));

	assert(ltot >= sizeof *o + soc->lhttp + soc->wsl);

	o = ptr;
	memset(o, 0, sizeof *o);
	o->magic = OBJECT_MAGIC;

	l = PRNDDN(ltot - (sizeof *o + soc->lhttp));
	assert(l >= soc->wsl);

	o->http = HTTP_create(o + 1, soc->nhttp);
	WS_Init(o->ws_o, "obj", (char *)(o + 1) + soc->lhttp, soc->wsl);
	WS_Assert(o->ws_o);
	assert(o->ws_o->e <= (char*)ptr + ltot);

	http_Setup(o->http, o->ws_o);
	o->http->magic = HTTP_MAGIC;
	o->entered = NAN;
	o->exp = *soc->exp;
	VTAILQ_INIT(&o->store);
	sp->wrk->stats.n_object++;

	if (sp->objcore != NULL) {
		CHECK_OBJ_NOTNULL(sp->objcore, OBJCORE_MAGIC);

		o->objcore = sp->objcore;
		sp->objcore = NULL;
		BAN_NewObjCore(o->objcore);

		o->objcore->methods = &default_oc_methods;
		o->objcore->priv = o;
	}
	return (o);
}
