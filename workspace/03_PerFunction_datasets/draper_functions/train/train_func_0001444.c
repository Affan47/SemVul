VGZ_NewUngzip(struct sess *sp, const char *id)
{
	struct vgz *vg;

	CHECK_OBJ_NOTNULL(sp, SESS_MAGIC);
	vg = vgz_alloc_vgz(sp, id);
	vg->dir = VGZ_UN;
	VSC_C_main->n_gunzip++;


	assert(Z_OK == inflateInit2(&vg->vz, 31));
	return (vg);
}
