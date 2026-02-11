VSM_Abandoned(const struct VSM_data *vd)
{
	struct stat st;

	CHECK_OBJ_NOTNULL(vd, VSM_MAGIC);

	if (vd->head == NULL)
		return (1);

	if (!vd->head->alloc_seq)
		return (1);
	if (!stat(vd->fname, &st))
		return (1);
	if (st.st_dev != vd->fstat.st_dev)
		return (1);
	if (st.st_ino != vd->fstat.st_ino)
		return (1);
	return (0);
}
