lpfc_fcp_cpu_map_show(struct device *dev, struct device_attribute *attr,
		      char *buf)
{
	struct Scsi_Host  *shost = class_to_shost(dev);
	struct lpfc_vport *vport = (struct lpfc_vport *)shost->hostdata;
	struct lpfc_hba   *phba = vport->phba;
	struct lpfc_vector_map_info *cpup;
	int  len = 0;

	if ((phba->sli_rev != LPFC_SLI_REV4) ||
	    (phba->intr_type != MSIX))
		return len;

	switch (phba->cfg_fcp_cpu_map) {
	case 0:
		len += snprintf(buf + len, PAGE_SIZE-len,
				"fcp_cpu_map: No mapping (%d)\n",
				phba->cfg_fcp_cpu_map);
		return len;
	case 1:
		len += snprintf(buf + len, PAGE_SIZE-len,
				"fcp_cpu_map: HBA centric mapping (%d): "
				"%d online CPUs\n",
				phba->cfg_fcp_cpu_map,
				phba->sli4_hba.num_online_cpu);
		break;
	case 2:
		len += snprintf(buf + len, PAGE_SIZE-len,
				"fcp_cpu_map: Driver centric mapping (%d): "
				"%d online CPUs\n",
				phba->cfg_fcp_cpu_map,
				phba->sli4_hba.num_online_cpu);
		break;
	}

	while (phba->sli4_hba.curr_disp_cpu < phba->sli4_hba.num_present_cpu) {
		cpup = &phba->sli4_hba.cpu_map[phba->sli4_hba.curr_disp_cpu];


		if (cpup->irq == LPFC_VECTOR_MAP_EMPTY)
			len += snprintf(buf + len, PAGE_SIZE-len,
					"CPU %02d io_chan %02d "
					"physid %d coreid %d\n",
					phba->sli4_hba.curr_disp_cpu,
					cpup->channel_id, cpup->phys_id,
					cpup->core_id);
		else
			len += snprintf(buf + len, PAGE_SIZE-len,
					"CPU %02d io_chan %02d "
					"physid %d coreid %d IRQ %d\n",
					phba->sli4_hba.curr_disp_cpu,
					cpup->channel_id, cpup->phys_id,
					cpup->core_id, cpup->irq);

		phba->sli4_hba.curr_disp_cpu++;


		if (phba->sli4_hba.curr_disp_cpu <
				phba->sli4_hba.num_present_cpu &&
				(len >= (PAGE_SIZE - 64))) {
			len += snprintf(buf + len, PAGE_SIZE-len, "more...\n");
			break;
		}
	}

	if (phba->sli4_hba.curr_disp_cpu == phba->sli4_hba.num_present_cpu)
		phba->sli4_hba.curr_disp_cpu = 0;

	return len;
}
