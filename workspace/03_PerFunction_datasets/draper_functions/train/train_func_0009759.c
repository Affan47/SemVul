rtc_irq_unregister(struct rtc_device *rtc, struct rtc_task *task)
{
	spin_lock_irq(&rtc->irq_task_lock);
	if (rtc->irq_task == task)
		rtc->irq_task = NULL;
	spin_unlock_irq(&rtc->irq_task_lock);
}
