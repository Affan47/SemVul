vfp_esi_end(struct sess *sp)
{
	struct vsb *vsb;
	struct vef_priv *vef;
	ssize_t l;

	CHECK_OBJ_NOTNULL(sp, SESS_MAGIC);
	AN(sp->wrk->vep);

	vsb = VEP_Finish(sp);

	if (vsb != NULL) {
		l = VSB_len(vsb);
		assert(l > 0);

		sp->obj->esidata = STV_alloc(sp, l);
		XXXAN(sp->obj->esidata);
		memcpy(sp->obj->esidata->ptr, VSB_data(vsb), l);
		sp->obj->esidata->len = l;
		VSB_delete(vsb);
	}
	if (sp->wrk->vgz_rx != NULL)
		VGZ_Destroy(&sp->wrk->vgz_rx);

	if (sp->wrk->vef_priv != NULL) {
		vef = sp->wrk->vef_priv;
		CHECK_OBJ_NOTNULL(vef, VEF_MAGIC);
		sp->wrk->vef_priv = NULL;
		VGZ_UpdateObj(vef->vgz, sp->obj);
		VGZ_Destroy(&vef->vgz);
		XXXAZ(vef->error);
		FREE_OBJ(vef);
	}
	return (0);
}
