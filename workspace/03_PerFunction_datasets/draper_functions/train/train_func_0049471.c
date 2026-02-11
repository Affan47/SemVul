VBE_ReleaseConn(struct vbc *vc)
{

	CHECK_OBJ_NOTNULL(vc, VBC_MAGIC);
	assert(vc->backend == NULL);
	assert(vc->fd < 0);

	vc->addr = NULL;
	vc->addrlen = 0;
	vc->recycled = 0;
	Lck_Lock(&VBE_mtx);
	VSC_C_main->n_vbc--;
	Lck_Unlock(&VBE_mtx);
	FREE_OBJ(vc);
}
