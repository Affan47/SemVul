VDI_RecycleFd(struct sess *sp)
{
	struct backend *bp;

	CHECK_OBJ_NOTNULL(sp->vbc, VBC_MAGIC);
	CHECK_OBJ_NOTNULL(sp->vbc->backend, BACKEND_MAGIC);
	assert(sp->vbc->fd >= 0);
	AZ(sp->wrk->do_close);

	bp = sp->vbc->backend;

	WSL(sp->wrk, SLT_BackendReuse, sp->vbc->fd, "%s", bp->vcl_name);


	WSL_Flush(sp->wrk, 0);
	Lck_Lock(&bp->mtx);
	VSC_C_main->backend_recycle++;
	VTAILQ_INSERT_HEAD(&bp->connlist, sp->vbc, list);
	sp->vbc = NULL;
	VBE_DropRefLocked(bp);
}
