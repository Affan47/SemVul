HSH_Unbusy(const struct sess *sp)
{
	struct object *o;
	struct objhead *oh;
	struct objcore *oc;

	CHECK_OBJ_NOTNULL(sp, SESS_MAGIC);
	o = sp->obj;
	CHECK_OBJ_NOTNULL(o, OBJECT_MAGIC);
	oc = o->objcore;
	CHECK_OBJ_NOTNULL(oc, OBJCORE_MAGIC);
	oh = oc->objhead;
	CHECK_OBJ(oh, OBJHEAD_MAGIC);

	AssertObjBusy(o);
	AN(oc->ban);
	assert(oc->refcnt > 0);
	assert(oh->refcnt > 0);
	if (o->ws_o->overflow)
		sp->wrk->stats.n_objoverflow++;
	if (params->diag_bitmap & 0x40)
		WSP(sp, SLT_Debug,
		    "Object %u workspace free %u", o->xid, WS_Free(o->ws_o));


	Lck_Lock(&oh->mtx);
	assert(oh->refcnt > 0);

	VTAILQ_REMOVE(&oh->objcs, oc, list);
	VTAILQ_INSERT_HEAD(&oh->objcs, oc, list);
	oc->flags &= ~OC_F_BUSY;
	AZ(sp->wrk->nbusyobj);
	sp->wrk->nbusyobj = oc->busyobj;
	oc->busyobj = NULL;
	if (oh->waitinglist != NULL)
		hsh_rush(oh);
	AN(oc->ban);
	Lck_Unlock(&oh->mtx);
	assert(oc_getobj(sp->wrk, oc) == o);
}
