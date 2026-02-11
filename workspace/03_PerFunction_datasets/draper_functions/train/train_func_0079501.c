ips_allocatescbs(ips_ha_t * ha)
{
	ips_scb_t *scb_p;
	IPS_SG_LIST ips_sg;
	int i;
	dma_addr_t command_dma, sg_dma;

	METHOD_TRACE("ips_allocatescbs", 1);


	ha->scbs =
	    pci_alloc_consistent(ha->pcidev, ha->max_cmds * sizeof (ips_scb_t),
				 &command_dma);
	if (ha->scbs == NULL)
		return 0;
	ips_sg.list =
	    pci_alloc_consistent(ha->pcidev,
				 IPS_SGLIST_SIZE(ha) * IPS_MAX_SG *
				 ha->max_cmds, &sg_dma);
	if (ips_sg.list == NULL) {
		pci_free_consistent(ha->pcidev,
				    ha->max_cmds * sizeof (ips_scb_t), ha->scbs,
				    command_dma);
		return 0;
	}

	memset(ha->scbs, 0, ha->max_cmds * sizeof (ips_scb_t));

	for (i = 0; i < ha->max_cmds; i++) {
		scb_p = &ha->scbs[i];
		scb_p->scb_busaddr = command_dma + sizeof (ips_scb_t) * i;

		if (IPS_USE_ENH_SGLIST(ha)) {
			scb_p->sg_list.enh_list =
			    ips_sg.enh_list + i * IPS_MAX_SG;
			scb_p->sg_busaddr =
			    sg_dma + IPS_SGLIST_SIZE(ha) * IPS_MAX_SG * i;
		} else {
			scb_p->sg_list.std_list =
			    ips_sg.std_list + i * IPS_MAX_SG;
			scb_p->sg_busaddr =
			    sg_dma + IPS_SGLIST_SIZE(ha) * IPS_MAX_SG * i;
		}


		if (i < ha->max_cmds - 1) {
			scb_p->q_next = ha->scb_freelist;
			ha->scb_freelist = scb_p;
		}
	}


	return (1);
}
