sym_abort_scsiio(struct sym_hcb *np, struct scsi_cmnd *cmd, int timed_out)
{
	struct sym_ccb *cp;
	SYM_QUEHEAD *qp;


	cp = NULL;
	FOR_EACH_QUEUED_ELEMENT(&np->busy_ccbq, qp) {
		struct sym_ccb *cp2 = sym_que_entry(qp, struct sym_ccb, link_ccbq);
		if (cp2->cmd == cmd) {
			cp = cp2;
			break;
		}
	}

	return sym_abort_ccb(np, cp, timed_out);
}
