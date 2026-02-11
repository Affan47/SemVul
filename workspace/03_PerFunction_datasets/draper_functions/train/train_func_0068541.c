turnipports_allocate_even(turnipports* tp, const ioa_addr *backend_addr, int allocate_rtcp,
				u64bits *reservation_token)
{
	int ret = -1;
	if (tp && backend_addr) {
		TURN_MUTEX_LOCK((const turn_mutex*)&(tp->mutex));
		turnports *t = turnipports_add(tp, STUN_ATTRIBUTE_TRANSPORT_UDP_VALUE, backend_addr);
		ret = turnports_allocate_even(t, allocate_rtcp, reservation_token);
		TURN_MUTEX_UNLOCK((const turn_mutex*)&(tp->mutex));
	}
	return ret;
}
