au_wkq_init(void)
{
	int err;

	err = 0;
	au_wkq = alloc_workqueue(AUFS_WKQ_NAME, 0, WQ_DFL_ACTIVE);
	if (IS_ERR(au_wkq))
		err = PTR_ERR(au_wkq);
	else if (!au_wkq)
		err = -ENOMEM;

	return err;
}
