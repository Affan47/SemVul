stop_initiator_timer(Timer *timer)
{
    debug("wap.wtp_init", 0, "stopping timer");
    gw_assert(timer);
    gwtimer_stop(timer);
}
