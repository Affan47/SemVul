read_local_name_complete(int index, read_local_name_rp *rp)
{
	struct dev_info *dev = &devs[index];

	DBG("hci%d status %u", index, rp->status);

	if (rp->status)
		return;

	memcpy(dev->name, rp->name, 248);

	if (!dev->pending) {
		update_name(index, (char *) rp->name);
		return;
	}

	hci_clear_bit(PENDING_NAME, &dev->pending);

	DBG("Got name for hci%d", index);

	if (!dev->pending && dev->up)
		init_adapter(index);
}
