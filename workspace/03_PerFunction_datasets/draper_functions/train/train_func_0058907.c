smt_send_ecf(struct s_smc *smc, struct fddi_addr *dest, int fc,
			 u_long tid, int type, int len)


{
	struct smt_ecf	*ecf ;
	SMbuf		*mb ;

	if (!(mb = smt_build_frame(smc,SMT_ECF,type,SMT_ECF_LEN + len)))
		return ;
	ecf = smtod(mb, struct smt_ecf *) ;

	smt_fill_echo(smc,&ecf->ec_echo,tid,len) ;
	ecf->smt.smt_dest = *dest ;
	ecf->smt.smt_tid = tid ;
	smc->mib.priv.fddiPRIVECF_Req_Tx++ ;
	smt_send_frame(smc,mb,fc,0) ;
}
