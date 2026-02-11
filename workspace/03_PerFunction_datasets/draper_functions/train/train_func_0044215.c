get_free_channel(struct cardstate *cs,
						  int cid)


{
	unsigned long flags;
	int i;
	struct at_state_t *ret;

	for (i = 0; i < cs->channels; ++i)
		if (gigaset_get_channel(cs->bcs + i) >= 0) {
			ret = &cs->bcs[i].at_state;
			ret->cid = cid;
			return ret;
		}

	spin_lock_irqsave(&cs->lock, flags);
	ret = kmalloc(sizeof(struct at_state_t), GFP_ATOMIC);
	if (ret) {
		gigaset_at_init(ret, NULL, cs, cid);
		list_add(&ret->list, &cs->temp_at_states);
	}
	spin_unlock_irqrestore(&cs->lock, flags);
	return ret;
}
