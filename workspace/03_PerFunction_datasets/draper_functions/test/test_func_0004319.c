speakup_con_update(struct vc_data *vc)
{
	unsigned long flags;

	if (speakup_console[vc->vc_num] == NULL || spk_parked)
		return;
	if (!spin_trylock_irqsave(&speakup_info.spinlock, flags))

		return;
	speakup_date(vc);
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
}
