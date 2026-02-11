prop_actions(struct s_smc *smc)
{
	int	port_in = 0 ;
	int	port_out = 0 ;

	RS_SET(smc,RS_EVENT) ;
	switch (smc->s.sas) {
	case SMT_SAS :
		port_in = port_out = pcm_get_s_port(smc) ;
		break ;
	case SMT_DAS :
		port_in = cfm_get_mac_input(smc) ;
		port_out = cfm_get_mac_output(smc) ;
		break ;
	case SMT_NAC :
		SMT_PANIC(smc,SMT_E0108, SMT_E0108_MSG) ;
		return ;
	}

	DB_ECM("ECM : prop_actions - trace_prop %d\n", smc->e.trace_prop,0) ;
	DB_ECM("ECM : prop_actions - in %d out %d\n", port_in,port_out) ;

	if (smc->e.trace_prop & ENTITY_BIT(ENTITY_MAC)) {

		DB_ECM("ECM : initiate TRACE on PHY %c\n",'A'+port_in-PA,0) ;
		queue_event(smc,EVENT_PCM+port_in,PC_TRACE) ;
	}
	else if ((smc->e.trace_prop & ENTITY_BIT(ENTITY_PHY(PA))) &&
		port_out != PA) {

		DB_ECM("ECM : propagate TRACE on PHY B\n",0,0) ;
		queue_event(smc,EVENT_PCMB,PC_TRACE) ;
	}
	else if ((smc->e.trace_prop & ENTITY_BIT(ENTITY_PHY(PB))) &&
		port_out != PB) {

		DB_ECM("ECM : propagate TRACE on PHY A\n",0,0) ;
		queue_event(smc,EVENT_PCMA,PC_TRACE) ;
	}
	else {

		DB_ECM("ECM : TRACE terminated\n",0,0) ;
		smc->e.path_test = PT_PENDING ;
	}
	smc->e.trace_prop = 0 ;
}
