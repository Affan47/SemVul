VBP_Remove(struct backend *b, struct vrt_backend_probe const *p)
{
	struct vbp_target *vt;
	struct vbp_vcl *vcl;
	void *ret;

	ASSERT_CLI();
	AN(p);
	CHECK_OBJ_NOTNULL(b, BACKEND_MAGIC);
	AN(b->probe);
	vt = b->probe;

	VTAILQ_FOREACH(vcl, &vt->vcls, list)
		if (vcl->probep == p)
			break;

	AN(vcl);

	Lck_Lock(&vbp_mtx);
	VTAILQ_REMOVE(&vt->vcls, vcl, list);
	Lck_Unlock(&vbp_mtx);

	FREE_OBJ(vcl);

	if (!VTAILQ_EMPTY(&vt->vcls))
		return;


	b->healthy = 1;

	vt->stop = 1;
	AZ(pthread_cancel(vt->thread));
	AZ(pthread_join(vt->thread, &ret));

	b->healthy = 1;

	VTAILQ_REMOVE(&vbp_list, vt, list);
	b->probe = NULL;
	VSB_delete(vt->vsb);
	FREE_OBJ(vt);
}
