mac_drv_rx_mode(struct s_smc *smc, int mode)
{
	switch(mode) {
	case RX_ENABLE_PASS_SMT:
		smc->os.hwm.pass_SMT = TRUE ;
		break ;
	case RX_DISABLE_PASS_SMT:
		smc->os.hwm.pass_SMT = FALSE ;
		break ;
	case RX_ENABLE_PASS_NSA:
		smc->os.hwm.pass_NSA = TRUE ;
		break ;
	case RX_DISABLE_PASS_NSA:
		smc->os.hwm.pass_NSA = FALSE ;
		break ;
	case RX_ENABLE_PASS_DB:
		smc->os.hwm.pass_DB = TRUE ;
		break ;
	case RX_DISABLE_PASS_DB:
		smc->os.hwm.pass_DB = FALSE ;
		break ;
	case RX_DISABLE_PASS_ALL:
		smc->os.hwm.pass_SMT = smc->os.hwm.pass_NSA = FALSE ;
		smc->os.hwm.pass_DB = FALSE ;
		smc->os.hwm.pass_llc_promisc = TRUE ;
		mac_set_rx_mode(smc,RX_DISABLE_NSA) ;
		break ;
	case RX_DISABLE_LLC_PROMISC:
		smc->os.hwm.pass_llc_promisc = FALSE ;
		break ;
	case RX_ENABLE_LLC_PROMISC:
		smc->os.hwm.pass_llc_promisc = TRUE ;
		break ;
	case RX_ENABLE_ALLMULTI:
	case RX_DISABLE_ALLMULTI:
	case RX_ENABLE_PROMISC:
	case RX_DISABLE_PROMISC:
	case RX_ENABLE_NSA:
	case RX_DISABLE_NSA:
	default:
		mac_set_rx_mode(smc,mode) ;
		break ;
	}
}
