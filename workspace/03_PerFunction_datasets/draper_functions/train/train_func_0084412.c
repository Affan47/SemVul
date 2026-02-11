cfm(struct s_smc *smc, int event)
{
	int	state ;
	int	cond ;
	int	oldstate ;


	all_selection_criteria (smc);


	cem_priv_state (smc, event);

	oldstate = smc->mib.fddiSMTCF_State ;
	do {
		DB_CFM("CFM : state %s%s",
			(smc->mib.fddiSMTCF_State & AFLAG) ? "ACTIONS " : "",
			cfm_states[smc->mib.fddiSMTCF_State & ~AFLAG]) ;
		DB_CFM(" event %s\n",cfm_events[event],0) ;
		state = smc->mib.fddiSMTCF_State ;
		cfm_fsm(smc,event) ;
		event = 0 ;
	} while (state != smc->mib.fddiSMTCF_State) ;

#ifndef	SLIM_SMT


	cond = FALSE ;
	if (	(smc->mib.fddiSMTCF_State == SC9_C_WRAP_A &&
		smc->y[PA].pc_mode == PM_PEER) 	||
		(smc->mib.fddiSMTCF_State == SC10_C_WRAP_B &&
		smc->y[PB].pc_mode == PM_PEER) 	||
		(smc->mib.fddiSMTCF_State == SC11_C_WRAP_S &&
		smc->y[PS].pc_mode == PM_PEER &&
		smc->y[PS].mib->fddiPORTNeighborType != TS ) ) {
			cond = TRUE ;
	}
	if (cond != smc->mib.fddiSMTPeerWrapFlag)
		smt_srf_event(smc,SMT_COND_SMT_PEER_WRAP,0,cond) ;

#if	0


	if (smc->mib.fddiSMTCF_State != oldstate) {
		smt_srf_event(smc,SMT_EVENT_MAC_PATH_CHANGE,INDEX_MAC,0) ;
	}
#endif
#endif


	smc->mib.m[MAC0].fddiMACDownstreamPORTType =
		cf_to_ptype[smc->mib.fddiSMTCF_State] ;
	cfm_state_change(smc,(int)smc->mib.fddiSMTCF_State) ;
}
