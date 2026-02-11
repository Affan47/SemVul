sh_cmt_stop(struct sh_cmt_channel *ch, unsigned long flag)
{
	unsigned long flags;
	unsigned long f;

	raw_spin_lock_irqsave(&ch->lock, flags);

	f = ch->flags & (FLAG_CLOCKEVENT | FLAG_CLOCKSOURCE);
	ch->flags &= ~flag;

	if (f && !(ch->flags & (FLAG_CLOCKEVENT | FLAG_CLOCKSOURCE)))
		sh_cmt_disable(ch);


	if ((flag == FLAG_CLOCKEVENT) && (ch->flags & FLAG_CLOCKSOURCE))
		__sh_cmt_set_next(ch, ch->max_match_value);

	raw_spin_unlock_irqrestore(&ch->lock, flags);
}
