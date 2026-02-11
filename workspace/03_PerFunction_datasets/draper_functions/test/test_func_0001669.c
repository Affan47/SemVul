asd_init_scb_sites(struct asd_ha_struct *asd_ha)
{
	u16	site_no;
	u16     max_scbs = 0;

	for (site_no = asd_ha->hw_prof.max_scbs-1;
	     site_no != (u16) -1;
	     site_no--) {
		u16	i;


		for (i = 0; i < ASD_SCB_SIZE; i += 4)
			asd_scbsite_write_dword(asd_ha, site_no, i, 0);


		asd_scbsite_write_byte(asd_ha, site_no,
				       offsetof(struct scb_header, opcode),
				       0xFF);


		asd_scbsite_write_byte(asd_ha, site_no, 0x49, 0x01);


		if (!SCB_SITE_VALID(site_no))
			continue;

		if (last_scb_site_no == 0)
			last_scb_site_no = site_no;


		asd_scbsite_write_word(asd_ha, site_no, 0, first_scb_site_no);

		first_scb_site_no = site_no;
		max_scbs++;
	}
	asd_ha->hw_prof.max_scbs = max_scbs;
	ASD_DPRINTK("max_scbs:%d\n", asd_ha->hw_prof.max_scbs);
	ASD_DPRINTK("first_scb_site_no:0x%x\n", first_scb_site_no);
	ASD_DPRINTK("last_scb_site_no:0x%x\n", last_scb_site_no);
}
