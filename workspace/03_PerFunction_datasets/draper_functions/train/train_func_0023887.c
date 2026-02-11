_ocrdma_alloc_pd(struct ocrdma_dev *dev,
					  struct ocrdma_ucontext *uctx,
					  struct ib_udata *udata)
{
	struct ocrdma_pd *pd = NULL;
	int status = 0;

	pd = kzalloc(sizeof(*pd), GFP_KERNEL);
	if (!pd)
		return ERR_PTR(-ENOMEM);

	if (udata && uctx && dev->attr.max_dpp_pds) {
		pd->dpp_enabled =
			ocrdma_get_asic_type(dev) == OCRDMA_ASIC_GEN_SKH_R;
		pd->num_dpp_qp =
			pd->dpp_enabled ? (dev->nic_info.db_page_size /
					   dev->attr.wqe_size) : 0;
	}

	if (dev->pd_mgr->pd_prealloc_valid) {
		status = ocrdma_get_pd_num(dev, pd);
		if (status == 0) {
			return pd;
		} else {
			kfree(pd);
			return ERR_PTR(status);
		}
	}

retry:
	status = ocrdma_mbx_alloc_pd(dev, pd);
	if (status) {
		if (pd->dpp_enabled) {
			pd->dpp_enabled = false;
			pd->num_dpp_qp = 0;
			goto retry;
		} else {
			kfree(pd);
			return ERR_PTR(status);
		}
	}

	return pd;
}
