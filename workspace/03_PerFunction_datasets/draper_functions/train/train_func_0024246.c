mei_me_pg_legacy_intr(struct mei_device *dev)
{
	struct mei_me_hw *hw = to_me_hw(dev);

	if (dev->pg_event != MEI_PG_EVENT_INTR_WAIT)
		return;

	dev->pg_event = MEI_PG_EVENT_INTR_RECEIVED;
	hw->pg_state = MEI_PG_OFF;
	if (waitqueue_active(&dev->wait_pg))
		wake_up(&dev->wait_pg);
}
