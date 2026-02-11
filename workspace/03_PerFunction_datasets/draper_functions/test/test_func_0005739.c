reset_counters(int extended, int timeout, int mask,
			   ib_portid_t * portid, int port)
{
	memset(pc, 0, sizeof(pc));
	if (extended != 1) {
		if (!performance_reset_via(pc, portid, port, mask, timeout,
					   IB_GSI_PORT_COUNTERS, srcport))
			IBERROR("perf reset");
	} else {
		if (!performance_reset_via(pc, portid, port, mask, timeout,
					   IB_GSI_PORT_COUNTERS_EXT, srcport))
			IBERROR("perf ext reset");
	}
}
