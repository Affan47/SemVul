sym_abort_ccb(struct sym_hcb *np, struct sym_ccb *cp, int timed_out)
{


	if (!cp || !cp->host_status || cp->host_status == HS_WAIT)
		return -1;


	if (cp->to_abort) {
		sym_reset_scsi_bus(np, 1);
		return 0;
	}


	cp->to_abort = timed_out ? 2 : 1;


	np->istat_sem = SEM;
	OUTB(np, nc_istat, SIGP|SEM);
	return 0;
}
