VBE_DropRefVcl(struct backend *b)
{

	CHECK_OBJ_NOTNULL(b, BACKEND_MAGIC);

	Lck_Lock(&b->mtx);
	b->vsc->vcls--;
	VBE_DropRefLocked(b);
}
