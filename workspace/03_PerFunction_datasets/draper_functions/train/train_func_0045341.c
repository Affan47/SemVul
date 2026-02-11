qib_alloc_mr(struct ib_pd *pd,
			   enum ib_mr_type mr_type,
			   u32 max_num_sg)
{
	struct qib_mr *mr;

	if (mr_type != IB_MR_TYPE_MEM_REG)
		return ERR_PTR(-EINVAL);

	mr = alloc_mr(max_num_sg, pd);
	if (IS_ERR(mr))
		return (struct ib_mr *)mr;

	mr->pages = kcalloc(max_num_sg, sizeof(u64), GFP_KERNEL);
	if (!mr->pages)
		goto err;

	return &mr->ibmr;

err:
	qib_dereg_mr(&mr->ibmr);
	return ERR_PTR(-ENOMEM);
}
