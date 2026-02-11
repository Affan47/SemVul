kill_pes(pes_packet *p){
	if (p->pack_header)
		free(p->pack_header);
	if (p->pes_ext)
		free(p->pes_ext);
	if (p->pes_pckt_data)
		free(p->pes_pckt_data);
	if (p->mpeg1_headr)
		free(p->mpeg1_headr);
	init_pes(p);
}
