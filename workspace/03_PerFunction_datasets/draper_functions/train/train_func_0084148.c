qibfs_add(struct qib_devdata *dd)
{
	int ret;


	if (qib_super == NULL)
		ret = 0;
	else
		ret = add_cntr_files(qib_super, dd);
	return ret;
}
