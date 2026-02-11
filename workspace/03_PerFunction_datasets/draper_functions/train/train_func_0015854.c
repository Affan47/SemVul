stop_rmt_timer0(struct s_smc *smc)
{
	if (smc->r.rmt_timer0.tm_active)
		smt_timer_stop(smc,&smc->r.rmt_timer0) ;
}
