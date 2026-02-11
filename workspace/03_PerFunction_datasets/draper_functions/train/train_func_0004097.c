smc_read_elem_status (struct smc_ctrl_block *smc)
{
	struct smc_scsi_req *	sr = &smc->scsi_req;
	unsigned char		data[8192];
	int			rc;

  retry:
	bzero (sr, sizeof *sr);
	bzero (data, sizeof data);
	bzero (&smc->elem_desc, sizeof smc->elem_desc);
	smc->n_elem_desc = 0;
	smc->valid_elem_desc = 0;

	sr->n_cmd = 12;
	sr->cmd[0] = SCSI_CMD_READ_ELEMENT_STATUS;
	if (!smc->dont_ask_for_voltags) {
		sr->cmd[1] = 0x10;
	} else {
		sr->cmd[1] = 0x00;
	}
	sr->cmd[2] = 0;
	sr->cmd[3] = 0;
	sr->cmd[4] = 0;
	sr->cmd[5] = SMC_MAX_ELEMENT;
	sr->cmd[6] = 0;
	SMC_PUT3 (&sr->cmd[7], sizeof data);
	sr->cmd[10] = 0;

	sr->data = data;
	sr->n_data_avail = sizeof data;
	sr->data_dir = SMCSR_DD_IN;

	rc = smc_scsi_xa (smc);
	if (rc != 0) {
		if (smc->dont_ask_for_voltags)
			return rc;
		smc->dont_ask_for_voltags = 1;
		goto retry;
	}

	rc = smc_parse_element_status_data ((void*)data, sr->n_data_done,
				smc->elem_desc, SMC_MAX_ELEMENT);
	if (rc < 0) {
		strcpy (smc->errmsg, "elem_status format error");
		return -1;
	}

	smc->n_elem_desc = rc;

	smc->valid_elem_aa = 1;

	return 0;
}
