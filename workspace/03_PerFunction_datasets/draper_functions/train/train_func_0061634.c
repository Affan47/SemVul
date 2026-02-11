mthca_alloc_ucontext(struct ib_device *ibdev,
						struct ib_udata *udata)
{
	struct mthca_alloc_ucontext_resp uresp;
	struct mthca_ucontext           *context;
	int                              err;

	if (!(to_mdev(ibdev)->active))
		return ERR_PTR(-EAGAIN);

	memset(&uresp, 0, sizeof uresp);

	uresp.qp_tab_size = to_mdev(ibdev)->limits.num_qps;
	if (mthca_is_memfree(to_mdev(ibdev)))
		uresp.uarc_size = to_mdev(ibdev)->uar_table.uarc_size;
	else
		uresp.uarc_size = 0;

	context = kmalloc(sizeof *context, GFP_KERNEL);
	if (!context)
		return ERR_PTR(-ENOMEM);

	err = mthca_uar_alloc(to_mdev(ibdev), &context->uar);
	if (err) {
		kfree(context);
		return ERR_PTR(err);
	}

	context->db_tab = mthca_init_user_db_tab(to_mdev(ibdev));
	if (IS_ERR(context->db_tab)) {
		err = PTR_ERR(context->db_tab);
		mthca_uar_free(to_mdev(ibdev), &context->uar);
		kfree(context);
		return ERR_PTR(err);
	}

	if (ib_copy_to_udata(udata, &uresp, sizeof uresp)) {
		mthca_cleanup_user_db_tab(to_mdev(ibdev), &context->uar, context->db_tab);
		mthca_uar_free(to_mdev(ibdev), &context->uar);
		kfree(context);
		return ERR_PTR(-EFAULT);
	}

	context->reg_mr_warned = 0;

	return &context->ibucontext;
}
