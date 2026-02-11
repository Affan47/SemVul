nic_config_rss(struct nicpf *nic, struct rss_cfg_msg *cfg)
{
	u8  qset, idx = 0;
	u64 cpi_cfg, cpi_base, rssi_base, rssi;
	u64 idx_addr;

	rssi_base = nic->rssi_base[cfg->vf_id] + cfg->tbl_offset;

	rssi = rssi_base;
	qset = cfg->vf_id;

	for (; rssi < (rssi_base + cfg->tbl_len); rssi++) {
		u8 svf = cfg->ind_tbl[idx] >> 3;

		if (svf)
			qset = nic->vf_sqs[cfg->vf_id][svf - 1];
		else
			qset = cfg->vf_id;
		nic_reg_write(nic, NIC_PF_RSSI_0_4097_RQ | (rssi << 3),
			      (qset << 3) | (cfg->ind_tbl[idx] & 0x7));
		idx++;
	}

	cpi_base = nic->cpi_base[cfg->vf_id];
	if (pass1_silicon(nic->pdev))
		idx_addr = NIC_PF_CPI_0_2047_CFG;
	else
		idx_addr = NIC_PF_MPI_0_2047_CFG;
	cpi_cfg = nic_reg_read(nic, idx_addr | (cpi_base << 3));
	cpi_cfg &= ~(0xFULL << 20);
	cpi_cfg |= (cfg->hash_bits << 20);
	nic_reg_write(nic, idx_addr | (cpi_base << 3), cpi_cfg);
}
