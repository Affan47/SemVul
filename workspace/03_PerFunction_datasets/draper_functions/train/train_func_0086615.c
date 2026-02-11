sh_cmt_clock_event_next(unsigned long delta,
				   struct clock_event_device *ced)
{
	struct sh_cmt_channel *ch = ced_to_sh_cmt(ced);

	BUG_ON(!clockevent_state_oneshot(ced));
	if (likely(ch->flags & FLAG_IRQCONTEXT))
		ch->next_match_value = delta - 1;
	else
		sh_cmt_set_next(ch, delta - 1);

	return 0;
}
