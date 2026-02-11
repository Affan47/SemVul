cm109_toggle_buzzer_async(struct cm109_dev *dev)
{
	unsigned long flags;

	spin_lock_irqsave(&dev->ctl_submit_lock, flags);

	if (dev->ctl_urb_pending) {

		dev->buzzer_pending = 1;
	} else {
		dev->ctl_urb_pending = 1;
		cm109_submit_buzz_toggle(dev);
	}

	spin_unlock_irqrestore(&dev->ctl_submit_lock, flags);
}
