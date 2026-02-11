VEP_Finish(const struct worker *wrk)
{
	struct vep_state *vep;
	ssize_t l, lcb;

	CHECK_OBJ_NOTNULL(wrk, WORKER_MAGIC);
	CHECK_OBJ_NOTNULL(wrk->busyobj, BUSYOBJ_MAGIC);
	vep = wrk->busyobj->vep;
	CHECK_OBJ_NOTNULL(vep, VEP_MAGIC);

	if (vep->o_pending)
		vep_mark_common(vep, vep->ver_p, vep->last_mark);
	if (vep->o_wait > 0) {
		lcb = vep->cb(vep->wrk, 0, VGZ_ALIGN);
		vep_emit_common(vep, lcb - vep->o_last, vep->last_mark);
	}
	(void)vep->cb(vep->wrk, 0, VGZ_FINISH);

	wrk->busyobj->vep = NULL;
	AZ(VSB_finish(vep->vsb));
	l = VSB_len(vep->vsb);
	if (vep->esi_found && l > 0)
		return (vep->vsb);
	VSB_delete(vep->vsb);
	return (NULL);
}
