mptsas_free_fw_event(MPT_ADAPTER *ioc, struct fw_event_work *fw_event)
{
	unsigned long flags;

	spin_lock_irqsave(&ioc->fw_event_lock, flags);
	devtprintk(ioc, printk(MYIOC_s_DEBUG_FMT "%s: kfree (fw_event=0x%p)\n",
	    ioc->name, __func__, fw_event));
	list_del(&fw_event->list);
	kfree(fw_event);
	spin_unlock_irqrestore(&ioc->fw_event_lock, flags);
}
