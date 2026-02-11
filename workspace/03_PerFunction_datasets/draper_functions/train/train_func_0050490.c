usnic_ib_reg_mr(struct ib_pd *pd, u64 start, u64 length,
					u64 virt_addr, int access_flags,
					struct ib_udata *udata)
{
	struct usnic_ib_mr *mr;
	int err;

	usnic_dbg("start 0x%llx va 0x%llx length 0x%llx\n", start,
			virt_addr, length);

	mr = kzalloc(sizeof(*mr), GFP_KERNEL);
	if (IS_ERR_OR_NULL(mr))
		return ERR_PTR(mr ? PTR_ERR(mr) : -ENOMEM);

	mr->umem = usnic_uiom_reg_get(to_upd(pd)->umem_pd, start, length,
					access_flags, 0);
	if (IS_ERR_OR_NULL(mr->umem)) {
		err = mr->umem ? PTR_ERR(mr->umem) : -EFAULT;
		goto err_free;
	}

	mr->ibmr.lkey = mr->ibmr.rkey = 0;
	return &mr->ibmr;

err_free:
	kfree(mr);
	return ERR_PTR(err);
}
