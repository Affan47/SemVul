mlx5_ib_reg_user_mr(struct ib_pd *pd, u64 start, u64 length,
				  u64 virt_addr, int access_flags,
				  struct ib_udata *udata)
{
	struct mlx5_ib_dev *dev = to_mdev(pd->device);
	struct mlx5_ib_mr *mr = NULL;
	struct ib_umem *umem;
	int page_shift;
	int npages;
	int ncont;
	int order;
	int err;

	mlx5_ib_dbg(dev, "start 0x%llx, virt_addr 0x%llx, length 0x%llx, access_flags 0x%x\n",
		    start, virt_addr, length, access_flags);
	umem = ib_umem_get(pd->uobject->context, start, length, access_flags,
			   0);
	if (IS_ERR(umem)) {
		mlx5_ib_dbg(dev, "umem get failed (%ld)\n", PTR_ERR(umem));
		return (void *)umem;
	}

	mlx5_ib_cont_pages(umem, start, &npages, &page_shift, &ncont, &order);
	if (!npages) {
		mlx5_ib_warn(dev, "avoid zero region\n");
		err = -EINVAL;
		goto error;
	}

	mlx5_ib_dbg(dev, "npages %d, ncont %d, order %d, page_shift %d\n",
		    npages, ncont, order, page_shift);

	if (use_umr(order)) {
		mr = reg_umr(pd, umem, virt_addr, length, ncont, page_shift,
			     order, access_flags);
		if (PTR_ERR(mr) == -EAGAIN) {
			mlx5_ib_dbg(dev, "cache empty for order %d", order);
			mr = NULL;
		}
	} else if (access_flags & IB_ACCESS_ON_DEMAND) {
		err = -EINVAL;
		pr_err("Got MR registration for ODP MR > 512MB, not supported for Connect-IB");
		goto error;
	}

	if (!mr)
		mr = reg_create(pd, virt_addr, length, umem, ncont, page_shift,
				access_flags);

	if (IS_ERR(mr)) {
		err = PTR_ERR(mr);
		goto error;
	}

	mlx5_ib_dbg(dev, "mkey 0x%x\n", mr->mmr.key);

	mr->umem = umem;
	mr->npages = npages;
	atomic_add(npages, &dev->mdev->priv.reg_pages);
	mr->ibmr.lkey = mr->mmr.key;
	mr->ibmr.rkey = mr->mmr.key;

#ifdef CONFIG_INFINIBAND_ON_DEMAND_PAGING
	if (umem->odp_data) {


		smp_wmb();
		mr->umem->odp_data->private = mr;


		smp_wmb();
	}
#endif

	return &mr->ibmr;

error:
	ib_umem_release(umem);
	return ERR_PTR(err);
}
