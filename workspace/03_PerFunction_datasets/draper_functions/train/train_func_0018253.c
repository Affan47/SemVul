cfm_get_mac_input(struct s_smc *smc)
{
	return (smc->mib.fddiSMTCF_State == SC10_C_WRAP_B ||
		smc->mib.fddiSMTCF_State == SC5_THRU_B) ? PB : PA;
}
