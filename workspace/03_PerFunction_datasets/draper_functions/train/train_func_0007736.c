myri10ge_ss_init_lock(struct myri10ge_slice_state *ss)
{
	spin_lock_init(&ss->lock);
	ss->state = SLICE_STATE_IDLE;
}
