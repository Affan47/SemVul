wd_cmd_sel_atn (void)
{
#if WD33C93_DEBUG > 0
	write_log (_T("* %s select with atn, ID=%d\n"), WD33C93, wdregs[WD_DESTINATION_ID] & 0x7);
#endif
	wd_phase = 0;
	wdregs[WD_COMMAND_PHASE] = 0;
	if (SCSIID) {
		wd_phase = CSR_SELECT;
		set_status (wd_phase, 1);
		wdregs[WD_COMMAND_PHASE] = 0x10;
		return;
	}
	set_status (CSR_TIMEOUT, 1000);
}
