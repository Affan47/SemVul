AdvResetChipAndSB(ADV_DVC_VAR *asc_dvc)
{
	int status;
	ushort wdtr_able, sdtr_able, tagqng_able;
	ushort ppr_able = 0;
	uchar tid, max_cmd[ADV_MAX_TID + 1];
	AdvPortAddr iop_base;
	ushort bios_sig;

	iop_base = asc_dvc->iop_base;


	AdvReadWordLram(iop_base, ASC_MC_WDTR_ABLE, wdtr_able);
	AdvReadWordLram(iop_base, ASC_MC_SDTR_ABLE, sdtr_able);
	if (asc_dvc->chip_type == ADV_CHIP_ASC38C1600) {
		AdvReadWordLram(iop_base, ASC_MC_PPR_ABLE, ppr_able);
	}
	AdvReadWordLram(iop_base, ASC_MC_TAGQNG_ABLE, tagqng_able);
	for (tid = 0; tid <= ADV_MAX_TID; tid++) {
		AdvReadByteLram(iop_base, ASC_MC_NUMBER_OF_MAX_CMD + tid,
				max_cmd[tid]);
	}


	AdvReadWordLram(iop_base, ASC_MC_BIOS_SIGNATURE, bios_sig);
	AdvWriteWordLram(iop_base, ASC_MC_BIOS_SIGNATURE, 0);


	AdvWriteWordRegister(iop_base, IOPW_RISC_CSR, ADV_RISC_CSR_STOP);
	AdvWriteWordRegister(iop_base, IOPW_CTRL_REG, ADV_CTRL_REG_CMD_RESET);
	mdelay(100);
	AdvWriteWordRegister(iop_base, IOPW_CTRL_REG,
			     ADV_CTRL_REG_CMD_WR_IO_REG);


	asc_dvc->err_code = 0;
	if (asc_dvc->chip_type == ADV_CHIP_ASC38C1600) {
		status = AdvInitAsc38C1600Driver(asc_dvc);
	} else if (asc_dvc->chip_type == ADV_CHIP_ASC38C0800) {
		status = AdvInitAsc38C0800Driver(asc_dvc);
	} else {
		status = AdvInitAsc3550Driver(asc_dvc);
	}


	if (status == 0) {
		status = ADV_TRUE;
	} else {
		status = ADV_FALSE;
	}


	AdvWriteWordLram(iop_base, ASC_MC_BIOS_SIGNATURE, bios_sig);


	AdvWriteWordLram(iop_base, ASC_MC_WDTR_ABLE, wdtr_able);
	AdvWriteWordLram(iop_base, ASC_MC_SDTR_ABLE, sdtr_able);
	if (asc_dvc->chip_type == ADV_CHIP_ASC38C1600) {
		AdvWriteWordLram(iop_base, ASC_MC_PPR_ABLE, ppr_able);
	}
	AdvWriteWordLram(iop_base, ASC_MC_TAGQNG_ABLE, tagqng_able);
	for (tid = 0; tid <= ADV_MAX_TID; tid++) {
		AdvWriteByteLram(iop_base, ASC_MC_NUMBER_OF_MAX_CMD + tid,
				 max_cmd[tid]);
	}

	return status;
}
