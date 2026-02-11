vfp_esi_begin(struct worker *wrk, size_t estimate)
{
	struct busyobj *bo;
	struct vef_priv *vef;

	(void)estimate;
	CHECK_OBJ_NOTNULL(wrk, WORKER_MAGIC);
	bo = wrk->busyobj;
	CHECK_OBJ_NOTNULL(bo, BUSYOBJ_MAGIC);

	AZ(bo->vgz_rx);
	if (bo->is_gzip && bo->do_gunzip) {
		bo->vgz_rx = VGZ_NewUngzip(wrk, "U F E");
		VEP_Init(wrk, NULL);
	} else if (bo->is_gunzip && bo->do_gzip) {
		ALLOC_OBJ(vef, VEF_MAGIC);
		AN(vef);
		vef->vgz = VGZ_NewGzip(wrk, "G F E");
		AZ(bo->vef_priv);
		bo->vef_priv = vef;
		VEP_Init(wrk, vfp_vep_callback);
	} else if (bo->is_gzip) {
		bo->vgz_rx = VGZ_NewUngzip(wrk, "U F E");
		ALLOC_OBJ(vef, VEF_MAGIC);
		AN(vef);
		vef->vgz = VGZ_NewGzip(wrk, "G F E");
		AZ(bo->vef_priv);
		bo->vef_priv = vef;
		VEP_Init(wrk, vfp_vep_callback);
	} else {
		AZ(bo->vef_priv);
		VEP_Init(wrk, NULL);
	}

	AN(bo->vep);
}
