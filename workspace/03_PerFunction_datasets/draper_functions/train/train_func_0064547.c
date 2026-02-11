mac_con_resource_index(struct s_smc *smc, int mac)
{
#ifdef	CONCENTRATOR
	SK_UNUSED(smc) ;
	SK_UNUSED(mac) ;
	return entity_to_index(smc, cem_get_downstream(smc, ENTITY_MAC));
#else
	SK_UNUSED(mac) ;
	switch (smc->mib.fddiSMTCF_State) {
	case SC9_C_WRAP_A :
	case SC5_THRU_B :
	case SC11_C_WRAP_S :
		return 1;
	case SC10_C_WRAP_B :
	case SC4_THRU_A :
		return 2;
	}
	return smc->s.sas == SMT_SAS ? 2 : 3;
#endif
}
