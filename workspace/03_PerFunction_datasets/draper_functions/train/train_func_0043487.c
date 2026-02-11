i7core_rdimm_check_mc_ecc_err(struct mem_ctl_info *mci)
{
	struct i7core_pvt *pvt = mci->pvt_info;
	u32 rcv[3][2];
	int i, new0, new1, new2;


	pci_read_config_dword(pvt->pci_mcr[2], MC_COR_ECC_CNT_0,
								&rcv[0][0]);
	pci_read_config_dword(pvt->pci_mcr[2], MC_COR_ECC_CNT_1,
								&rcv[0][1]);
	pci_read_config_dword(pvt->pci_mcr[2], MC_COR_ECC_CNT_2,
								&rcv[1][0]);
	pci_read_config_dword(pvt->pci_mcr[2], MC_COR_ECC_CNT_3,
								&rcv[1][1]);
	pci_read_config_dword(pvt->pci_mcr[2], MC_COR_ECC_CNT_4,
								&rcv[2][0]);
	pci_read_config_dword(pvt->pci_mcr[2], MC_COR_ECC_CNT_5,
								&rcv[2][1]);
	for (i = 0 ; i < 3; i++) {
		edac_dbg(3, "MC_COR_ECC_CNT%d = 0x%x; MC_COR_ECC_CNT%d = 0x%x\n",
			 (i * 2), rcv[i][0], (i * 2) + 1, rcv[i][1]);

		if (pvt->channel[i].dimms > 2) {
			new0 = DIMM_BOT_COR_ERR(rcv[i][0]);
			new1 = DIMM_TOP_COR_ERR(rcv[i][0]);
			new2 = DIMM_BOT_COR_ERR(rcv[i][1]);
		} else {
			new0 = DIMM_TOP_COR_ERR(rcv[i][0]) +
					DIMM_BOT_COR_ERR(rcv[i][0]);
			new1 = DIMM_TOP_COR_ERR(rcv[i][1]) +
					DIMM_BOT_COR_ERR(rcv[i][1]);
			new2 = 0;
		}

		i7core_rdimm_update_ce_count(mci, i, new0, new1, new2);
	}
}
