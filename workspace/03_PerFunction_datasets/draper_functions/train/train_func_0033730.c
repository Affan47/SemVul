HSH_DeleteObjHead(struct worker *w, struct objhead *oh)
{

	AZ(oh->refcnt);
	assert(VTAILQ_EMPTY(&oh->objcs));
	Lck_Delete(&oh->mtx);
	w->stats.n_objecthead--;
	FREE_OBJ(oh);
}
