set_txptr(struct s_smc *smc)
{
	outpw(FM_A(FM_CMDREG2),FM_IRSTQ) ;


	outpw(FM_A(FM_RPXA0),smc->hw.fp.fifo.tx_a0_start) ;
	outpw(FM_A(FM_SWPXA0),smc->hw.fp.fifo.tx_a0_start) ;
	outpw(FM_A(FM_WPXA0),smc->hw.fp.fifo.tx_a0_start) ;
	outpw(FM_A(FM_EAA0),smc->hw.fp.fifo.rx2_fifo_start-1) ;


	if (smc->hw.fp.fifo.tx_s_size) {
		outpw(FM_A(FM_RPXS),smc->hw.fp.fifo.tx_s_start) ;
		outpw(FM_A(FM_SWPXS),smc->hw.fp.fifo.tx_s_start) ;
		outpw(FM_A(FM_WPXS),smc->hw.fp.fifo.tx_s_start) ;
		outpw(FM_A(FM_EAS),smc->hw.fp.fifo.tx_a0_start-1) ;
	}
	else {
		outpw(FM_A(FM_RPXS),smc->hw.fp.fifo.tx_a0_start-1) ;
		outpw(FM_A(FM_SWPXS),smc->hw.fp.fifo.tx_a0_start-1) ;
		outpw(FM_A(FM_WPXS),smc->hw.fp.fifo.tx_a0_start-1) ;
		outpw(FM_A(FM_EAS),smc->hw.fp.fifo.tx_a0_start-1) ;
	}
}
