asd_seq_setup_seqs(struct asd_ha_struct *asd_ha)
{
	int 		lseq;
	u8		lseq_mask;


	asd_seq_init_ddb_sites(asd_ha);


	asd_init_scb_sites(asd_ha);


	asd_init_cseq_scratch(asd_ha);


	asd_init_lseq_scratch(asd_ha);


	asd_init_cseq_cio(asd_ha);

	asd_init_ddb_0(asd_ha);


	lseq_mask = asd_ha->hw_prof.enabled_phys;
	for_each_sequencer(lseq_mask, lseq_mask, lseq)
		asd_init_lseq_cio(asd_ha, lseq);
	asd_post_init_cseq(asd_ha);
}
