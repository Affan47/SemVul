i5000_get_error_info(struct mem_ctl_info *mci,
				 struct i5000_error_info *info)
{
	struct i5000_pvt *pvt;
	u32 value;

	pvt = mci->pvt_info;


	pci_read_config_dword(pvt->branchmap_werrors, FERR_FAT_FBD, &value);


	value &= (FERR_FAT_FBDCHAN | FERR_FAT_MASK);


	if (value & FERR_FAT_MASK) {
		info->ferr_fat_fbd = value;


		pci_read_config_dword(pvt->branchmap_werrors,
				NERR_FAT_FBD, &info->nerr_fat_fbd);
		pci_read_config_word(pvt->branchmap_werrors,
				NRECMEMA, &info->nrecmema);
		pci_read_config_dword(pvt->branchmap_werrors,
				NRECMEMB, &info->nrecmemb);


		pci_write_config_dword(pvt->branchmap_werrors,
				FERR_FAT_FBD, value);
	} else {
		info->ferr_fat_fbd = 0;
		info->nerr_fat_fbd = 0;
		info->nrecmema = 0;
		info->nrecmemb = 0;
	}


	pci_read_config_dword(pvt->branchmap_werrors, FERR_NF_FBD, &value);


	if (value & FERR_NF_MASK) {
		info->ferr_nf_fbd = value;


		pci_read_config_dword(pvt->branchmap_werrors,
				NERR_NF_FBD, &info->nerr_nf_fbd);
		pci_read_config_word(pvt->branchmap_werrors,
				RECMEMA, &info->recmema);
		pci_read_config_dword(pvt->branchmap_werrors,
				RECMEMB, &info->recmemb);
		pci_read_config_dword(pvt->branchmap_werrors,
				REDMEMB, &info->redmemb);


		pci_write_config_dword(pvt->branchmap_werrors,
				FERR_NF_FBD, value);
	} else {
		info->ferr_nf_fbd = 0;
		info->nerr_nf_fbd = 0;
		info->recmema = 0;
		info->recmemb = 0;
		info->redmemb = 0;
	}
}
