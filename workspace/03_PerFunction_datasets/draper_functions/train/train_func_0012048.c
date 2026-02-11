vfp_testgzip_end(struct sess *sp)
{
	struct vgz *vg;

	vg = sp->wrk->vgz_rx;
	sp->wrk->vgz_rx = NULL;
	CHECK_OBJ_NOTNULL(vg, VGZ_MAGIC);
	VGZ_UpdateObj(vg, sp->obj);
	VGZ_Destroy(&vg);
	return (0);
}
