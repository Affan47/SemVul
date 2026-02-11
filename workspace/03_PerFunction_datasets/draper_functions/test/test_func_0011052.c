rmt(struct s_smc *smc, int event)
{
	int	state ;

	do {
		DB_RMT("RMT : state %s%s",
			(smc->mib.m[MAC0].fddiMACRMTState & AFLAG) ? "ACTIONS " : "",
			rmt_states[smc->mib.m[MAC0].fddiMACRMTState & ~AFLAG]) ;
		DB_RMT(" event %s\n",rmt_events[event],0) ;
		state = smc->mib.m[MAC0].fddiMACRMTState ;
		rmt_fsm(smc,event) ;
		event = 0 ;
	} while (state != smc->mib.m[MAC0].fddiMACRMTState) ;
	rmt_state_change(smc,(int)smc->mib.m[MAC0].fddiMACRMTState) ;
}
