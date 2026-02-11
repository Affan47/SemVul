ocrdma_alloc_ucontext_pd(struct ocrdma_dev *dev,
				    struct ocrdma_ucontext *uctx,
				    struct ib_udata *udata)
{
	int status = 0;

	uctx->cntxt_pd = _ocrdma_alloc_pd(dev, uctx, udata);
	if (IS_ERR(uctx->cntxt_pd)) {
		status = PTR_ERR(uctx->cntxt_pd);
		uctx->cntxt_pd = NULL;
		goto err;
	}

	uctx->cntxt_pd->uctx = uctx;
	uctx->cntxt_pd->ibpd.device = &dev->ibdev;
err:
	return status;
}
