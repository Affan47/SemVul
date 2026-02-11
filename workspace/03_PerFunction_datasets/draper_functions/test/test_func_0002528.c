issue_scb(adapter_t *adapter, scb_t *scb)
{
	volatile mbox64_t	*mbox64 = adapter->mbox64;
	volatile mbox_t		*mbox = adapter->mbox;
	unsigned int	i = 0;

	if(unlikely(mbox->m_in.busy)) {
		do {
			udelay(1);
			i++;
		} while( mbox->m_in.busy && (i < max_mbox_busy_wait) );

		if(mbox->m_in.busy) return -1;
	}


	memcpy((char *)&mbox->m_out, (char *)scb->raw_mbox,
			sizeof(struct mbox_out));

	mbox->m_out.cmdid = scb->idx;
	mbox->m_in.busy = 1;


	atomic_inc(&adapter->pend_cmds);

	switch (mbox->m_out.cmd) {
	case MEGA_MBOXCMD_LREAD64:
	case MEGA_MBOXCMD_LWRITE64:
	case MEGA_MBOXCMD_PASSTHRU64:
	case MEGA_MBOXCMD_EXTPTHRU:
		mbox64->xfer_segment_lo = mbox->m_out.xferaddr;
		mbox64->xfer_segment_hi = 0;
		mbox->m_out.xferaddr = 0xFFFFFFFF;
		break;
	default:
		mbox64->xfer_segment_lo = 0;
		mbox64->xfer_segment_hi = 0;
	}


	scb->state |= SCB_ISSUED;

	if( likely(adapter->flag & BOARD_MEMMAP) ) {
		mbox->m_in.poll = 0;
		mbox->m_in.ack = 0;
		WRINDOOR(adapter, adapter->mbox_dma | 0x1);
	}
	else {
		irq_enable(adapter);
		issue_command(adapter);
	}

	return 0;
}
