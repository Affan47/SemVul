sm_ph_lem_start(struct s_smc *smc, int np, int threshold)
{
	struct lem_counter *lem = &smc->y[np].lem ;

	lem->lem_on = 1 ;
	lem->lem_errors = 0L ;


	outpw(PLC(np,PL_LE_THRESHOLD),threshold) ;
	(void)inpw(PLC(np,PL_LINK_ERR_CTR)) ;


	SETMASK(PLC(np,PL_INTR_MASK),PL_LE_CTR,PL_LE_CTR) ;
}
