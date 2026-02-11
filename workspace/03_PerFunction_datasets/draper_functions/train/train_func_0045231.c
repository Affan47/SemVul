np_down(unit, proto)
    int unit, proto;
{
    if (--num_np_up == 0 && idle_time_limit > 0) {
	UNTIMEOUT(check_idle, NULL);
    }
}
