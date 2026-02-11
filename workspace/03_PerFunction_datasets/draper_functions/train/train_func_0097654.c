initio_state_3(struct initio_host * host)
{
	struct scsi_ctrl_blk *scb = host->active;
	struct target_control *active_tc = host->active_tc;
	int i;

#if DEBUG_STATE
	printk("-s3-");
#endif
	for (;;) {
		switch (host->phase) {
		case CMD_OUT:
			for (i = 0; i < (int) scb->cdblen; i++)
				outb(scb->cdb[i], host->addr + TUL_SFifo);
			outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);
			if (wait_tulip(host) == -1)
				return -1;
			if (host->phase == CMD_OUT)
				return initio_bad_seq(host);
			return 4;

		case MSG_IN:
			scb->next_state = 3;
			if (initio_msgin(host) == -1)
				return -1;
			break;

		case STATUS_IN:
			if (initio_status_msg(host) == -1)
				return -1;
			break;

		case MSG_OUT:
			if (active_tc->flags & (TCF_SYNC_DONE | TCF_NO_SYNC_NEGO)) {
				outb(MSG_NOP, host->addr + TUL_SFifo);
				outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);
				if (wait_tulip(host) == -1)
					return -1;
			} else {
				active_tc->flags |= TCF_SYNC_DONE;

				outb(MSG_EXTEND, host->addr + TUL_SFifo);
				outb(3, host->addr + TUL_SFifo);
				outb(1, host->addr + TUL_SFifo);
				outb(initio_rate_tbl[active_tc->flags & TCF_SCSI_RATE], host->addr + TUL_SFifo);
				outb(MAX_OFFSET, host->addr + TUL_SFifo);
				outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);
				if (wait_tulip(host) == -1)
					return -1;
				outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0);
				outb(inb(host->addr + TUL_SSignal) & (TSC_SET_ACK | 7), host->addr + TUL_SSignal);

			}
			break;
		default:
			return initio_bad_seq(host);
		}
	}
}
