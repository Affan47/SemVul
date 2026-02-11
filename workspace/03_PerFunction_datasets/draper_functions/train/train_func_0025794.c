smt_send_rdf(struct s_smc *smc, SMbuf *rej, int fc, int reason,
			 int local)


{
	SMbuf	*mb ;
	struct smt_header	*sm ;
	struct smt_rdf	*rdf ;
	int		len ;
	int		frame_len ;

	sm = smtod(rej,struct smt_header *) ;
	if (sm->smt_type != SMT_REQUEST)
		return ;

	DB_SMT("SMT: sending RDF to %s,reason = 0x%x\n",
		addr_to_string(&sm->smt_source),reason) ;


	frame_len = rej->sm_len ;

	if (!(mb=smt_build_frame(smc,SMT_RDF,SMT_REPLY,sizeof(struct smt_rdf))))
		return ;
	rdf = smtod(mb,struct smt_rdf *) ;
	rdf->smt.smt_tid = sm->smt_tid ;
	rdf->smt.smt_dest = sm->smt_source ;


	rdf->reason.para.p_type = SMT_P_REASON ;
	rdf->reason.para.p_len = sizeof(struct smt_p_reason) - PARA_LEN ;
	rdf->reason.rdf_reason = reason ;


	rdf->version.para.p_type = SMT_P_VERSION ;
	rdf->version.para.p_len = sizeof(struct smt_p_version) - PARA_LEN ;
	rdf->version.v_pad = 0 ;
	rdf->version.v_n = 1 ;
	rdf->version.v_index = 1 ;
	rdf->version.v_version[0] = SMT_VID_2 ;
	rdf->version.v_pad2 = 0 ;


	if ((unsigned int) frame_len <= SMT_MAX_INFO_LEN - sizeof(*rdf) +
		2*sizeof(struct smt_header))
		len = frame_len ;
	else
		len = SMT_MAX_INFO_LEN - sizeof(*rdf) +
			2*sizeof(struct smt_header) ;

	len &= ~3 ;
	rdf->refused.para.p_type = SMT_P_REFUSED ;

	rdf->refused.para.p_len = len + 4 ;
	rdf->refused.ref_fc = fc ;


	smt_swap_para(sm,frame_len,0) ;

	memcpy((char *) &rdf->refused.ref_header,(char *) sm,len) ;

	len -= sizeof(struct smt_header) ;
	mb->sm_len += len ;
	rdf->smt.smt_len += len ;

	dump_smt(smc,(struct smt_header *)rdf,"RDF") ;
	smc->mib.priv.fddiPRIVRDF_Tx++ ;
	smt_send_frame(smc,mb,FC_SMT_INFO,local) ;
}
