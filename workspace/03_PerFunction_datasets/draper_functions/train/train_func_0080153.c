clock_gmt2loc(time_t stamp)
{
	if (GNET_PROPERTY(host_runs_ntp))
		return stamp;

	return stamp - (int32) GNET_PROPERTY(clock_skew);
}
