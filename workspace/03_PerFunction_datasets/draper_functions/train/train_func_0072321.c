mthca_init_arbel(struct mthca_dev *mdev)
{
	struct mthca_dev_lim        dev_lim;
	struct mthca_profile        profile;
	struct mthca_init_hca_param init_hca;
	s64 icm_size;
	int err;

	err = mthca_QUERY_FW(mdev);
	if (err) {
		mthca_err(mdev, "QUERY_FW command failed %d, aborting.\n", err);
		return err;
	}

	err = mthca_ENABLE_LAM(mdev);
	if (err == -EAGAIN) {
		mthca_dbg(mdev, "No HCA-attached memory (running in MemFree mode)\n");
		mdev->mthca_flags |= MTHCA_FLAG_NO_LAM;
	} else if (err) {
		mthca_err(mdev, "ENABLE_LAM returned %d, aborting.\n", err);
		return err;
	}

	err = mthca_load_fw(mdev);
	if (err) {
		mthca_err(mdev, "Loading FW returned %d, aborting.\n", err);
		goto err_disable;
	}

	err = mthca_dev_lim(mdev, &dev_lim);
	if (err) {
		mthca_err(mdev, "QUERY_DEV_LIM returned %d, aborting.\n", err);
		goto err_stop_fw;
	}

	profile = hca_profile;
	profile.num_uar  = dev_lim.uar_size / PAGE_SIZE;
	profile.num_udav = 0;
	if (mdev->mthca_flags & MTHCA_FLAG_SRQ)
		profile.num_srq = dev_lim.max_srqs;

	icm_size = mthca_make_profile(mdev, &profile, &dev_lim, &init_hca);
	if (icm_size < 0) {
		err = icm_size;
		goto err_stop_fw;
	}

	err = mthca_init_icm(mdev, &dev_lim, &init_hca, icm_size);
	if (err)
		goto err_stop_fw;

	err = mthca_INIT_HCA(mdev, &init_hca);
	if (err) {
		mthca_err(mdev, "INIT_HCA command returned %d, aborting.\n", err);
		goto err_free_icm;
	}

	return 0;

err_free_icm:
	mthca_free_icms(mdev);

err_stop_fw:
	mthca_UNMAP_FA(mdev);
	mthca_free_icm(mdev, mdev->fw.arbel.fw_icm, 0);

err_disable:
	if (!(mdev->mthca_flags & MTHCA_FLAG_NO_LAM))
		mthca_DISABLE_LAM(mdev);

	return err;
}
