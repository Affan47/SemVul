aim_rx_data(struct mbo *mbo)
{
	struct most_video_dev *mdev =
		get_aim_dev(mbo->ifp, mbo->hdm_channel_id);

	if (!mdev)
		return -EIO;

	spin_lock(&mdev->list_lock);
	if (unlikely(mdev->mute)) {
		spin_unlock(&mdev->list_lock);
		return -EIO;
	}

	list_add_tail(&mbo->list, &mdev->pending_mbos);
	spin_unlock(&mdev->list_lock);
	wake_up_interruptible(&mdev->wait_data);
	return 0;
}
