rbd_init(void)
{
	int rc;

	if (!libceph_compatible(NULL)) {
		rbd_warn(NULL, "libceph incompatibility (quitting)");
		return -EINVAL;
	}

	rc = rbd_slab_init();
	if (rc)
		return rc;


	rbd_wq = alloc_workqueue(RBD_DRV_NAME, WQ_MEM_RECLAIM, 0);
	if (!rbd_wq) {
		rc = -ENOMEM;
		goto err_out_slab;
	}

	if (single_major) {
		rbd_major = register_blkdev(0, RBD_DRV_NAME);
		if (rbd_major < 0) {
			rc = rbd_major;
			goto err_out_wq;
		}
	}

	rc = rbd_sysfs_init();
	if (rc)
		goto err_out_blkdev;

	if (single_major)
		pr_info("loaded (major %d)\n", rbd_major);
	else
		pr_info("loaded\n");

	return 0;

err_out_blkdev:
	if (single_major)
		unregister_blkdev(rbd_major, RBD_DRV_NAME);
err_out_wq:
	destroy_workqueue(rbd_wq);
err_out_slab:
	rbd_slab_exit();
	return rc;
}
