usnic_fwd_dev_ready_locked(struct usnic_fwd_dev *ufdev)
{
	lockdep_assert_held(&ufdev->lock);

	if (!ufdev->link_up)
		return -EPERM;

	return 0;
}
