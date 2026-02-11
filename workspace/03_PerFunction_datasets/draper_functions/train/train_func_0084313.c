hwt_wait_time(struct s_smc *smc, u_long start, long int duration)
{
	long	diff ;
	long	interval ;
	int	wrapped ;


	if (smc->hw.timer_activ == FALSE ||
		hwt_quick_read(smc) == hwt_quick_read(smc)) {
		return ;
	}

	interval = inpd(ADDR(B2_TI_INI)) ;
	if (interval > duration) {
		do {
			diff = (long)(start - hwt_quick_read(smc)) ;
			if (diff < 0) {
				diff += interval ;
			}
		} while (diff <= duration) ;
	}
	else {
		diff = interval ;
		wrapped = 0 ;
		do {
			if (!wrapped) {
				if (hwt_quick_read(smc) >= start) {
					diff += interval ;
					wrapped = 1 ;
				}
			}
			else {
				if (hwt_quick_read(smc) < start) {
					wrapped = 0 ;
				}
			}
		} while (diff <= duration) ;
	}
}
