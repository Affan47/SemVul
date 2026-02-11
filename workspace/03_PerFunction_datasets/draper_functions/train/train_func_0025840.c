cnt_lookup(struct sess *sp)
{
	struct objcore *oc;
	struct object *o;
	struct objhead *oh;

	CHECK_OBJ_NOTNULL(sp, SESS_MAGIC);
	CHECK_OBJ_NOTNULL(sp->vcl, VCL_CONF_MAGIC);

	if (sp->hash_objhead == NULL) {

		AZ(sp->vary_b);
		AZ(sp->vary_l);
		AZ(sp->vary_e);
		(void)WS_Reserve(sp->ws, 0);
		sp->vary_b = (void*)sp->ws->f;
		sp->vary_e = (void*)sp->ws->r;
		sp->vary_b[2] = '\0';
	}

	oc = HSH_Lookup(sp, &oh);

	if (oc == NULL) {


		return (1);
	}


	CHECK_OBJ_NOTNULL(oc, OBJCORE_MAGIC);
	CHECK_OBJ_NOTNULL(oh, OBJHEAD_MAGIC);


	if (oc->flags & OC_F_BUSY) {
		sp->wrk->stats.cache_miss++;

		if (sp->vary_l != NULL)
			WS_ReleaseP(sp->ws, (void*)sp->vary_l);
		else
			WS_Release(sp->ws, 0);
		sp->vary_b = NULL;
		sp->vary_l = NULL;
		sp->vary_e = NULL;

		sp->objcore = oc;
		sp->step = STP_MISS;
		return (0);
	}

	o = oc_getobj(sp->wrk, oc);
	CHECK_OBJ_NOTNULL(o, OBJECT_MAGIC);
	sp->obj = o;

	WS_Release(sp->ws, 0);
	sp->vary_b = NULL;
	sp->vary_l = NULL;
	sp->vary_e = NULL;

	if (oc->flags & OC_F_PASS) {
		sp->wrk->stats.cache_hitpass++;
		WSP(sp, SLT_HitPass, "%u", sp->obj->xid);
		(void)HSH_Deref(sp->wrk, NULL, &sp->obj);
                if (sp->stale_obj != NULL)
                    (void)HSH_Deref(sp->wrk, NULL, &sp->stale_obj);
		sp->objcore = NULL;
		sp->step = STP_PASS;
		return (0);
	}

	sp->wrk->stats.cache_hit++;
	WSP(sp, SLT_Hit, "%u", sp->obj->xid);
	sp->step = STP_HIT;
	return (0);
}
