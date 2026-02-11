mthca_init_hca(struct mthca_dev *mdev)
{
	int err;
	struct mthca_adapter adapter;

	if (mthca_is_memfree(mdev))
		err = mthca_init_arbel(mdev);
	else
		err = mthca_init_tavor(mdev);

	if (err)
		return err;

	err = mthca_QUERY_ADAPTER(mdev, &adapter);
	if (err) {
		mthca_err(mdev, "QUERY_ADAPTER command returned %d, aborting.\n", err);
		goto err_close;
	}

	mdev->eq_table.inta_pin = adapter.inta_pin;
	if (!mthca_is_memfree(mdev))
		mdev->rev_id = adapter.revision_id;
	memcpy(mdev->board_id, adapter.board_id, sizeof mdev->board_id);

	return 0;

err_close:
	mthca_close_hca(mdev);
	return err;
}
