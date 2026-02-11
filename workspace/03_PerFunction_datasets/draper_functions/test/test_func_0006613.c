VGZ_Destroy(struct vgz **vgp, int vsl_id)
{
	struct vgz *vg;
	int i;

	vg = *vgp;
	CHECK_OBJ_NOTNULL(vg, VGZ_MAGIC);
	*vgp = NULL;

	if (vsl_id < 0)
		WSLB(vg->wrk, SLT_Gzip, "%s %jd %jd %jd %jd %jd",
		    vg->id,
		    (intmax_t)vg->vz.total_in,
		    (intmax_t)vg->vz.total_out,
		    (intmax_t)vg->vz.start_bit,
		    (intmax_t)vg->vz.last_bit,
		    (intmax_t)vg->vz.stop_bit);
	else
		WSL(vg->wrk, SLT_Gzip, vsl_id, "%s %jd %jd %jd %jd %jd",
		    vg->id,
		    (intmax_t)vg->vz.total_in,
		    (intmax_t)vg->vz.total_out,
		    (intmax_t)vg->vz.start_bit,
		    (intmax_t)vg->vz.last_bit,
		    (intmax_t)vg->vz.stop_bit);
	if (vg->tmp != NULL)
		WS_Reset(vg->tmp, vg->tmp_snapshot);
	if (vg->dir == VGZ_GZ)
		i = deflateEnd(&vg->vz);
	else
		i = inflateEnd(&vg->vz);
	if (vg->last_i == Z_STREAM_END && i == Z_OK)
		i = Z_STREAM_END;
	FREE_OBJ(vg);
	if (i == Z_OK)
		return (VGZ_OK);
	if (i == Z_STREAM_END)
		return (VGZ_END);
	if (i == Z_BUF_ERROR)
		return (VGZ_STUCK);
	return (VGZ_ERROR);
}
