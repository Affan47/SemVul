osst_wait_ready(struct osst_tape * STp, struct osst_request ** aSRpnt,
				 unsigned timeout, int initial_delay)
{
	unsigned char		cmd[MAX_COMMAND_SIZE];
	struct osst_request   * SRpnt;
	unsigned long		startwait = jiffies;
#if DEBUG
	int			dbg  = debugging;
	char    	      * name = tape_name(STp);

	printk(OSST_DEB_MSG "%s:D: Reached onstream wait ready\n", name);
#endif

	if (initial_delay > 0)
		msleep(jiffies_to_msecs(initial_delay));

	memset(cmd, 0, MAX_COMMAND_SIZE);
	cmd[0] = TEST_UNIT_READY;

	SRpnt = osst_do_scsi(*aSRpnt, STp, cmd, 0, DMA_NONE, STp->timeout, MAX_RETRIES, 1);
	*aSRpnt = SRpnt;
	if (!SRpnt) return (-EBUSY);

	while ( STp->buffer->syscall_result && time_before(jiffies, startwait + timeout*HZ) &&
	       (( SRpnt->sense[2]  == 2 && SRpnt->sense[12] == 4    &&
		 (SRpnt->sense[13] == 1 || SRpnt->sense[13] == 8)    ) ||
		( SRpnt->sense[2]  == 6 && SRpnt->sense[12] == 0x28 &&
		  SRpnt->sense[13] == 0                                        )  )) {
#if DEBUG
	    if (debugging) {
		printk(OSST_DEB_MSG "%s:D: Sleeping in onstream wait ready\n", name);
		printk(OSST_DEB_MSG "%s:D: Turning off debugging for a while\n", name);
		debugging = 0;
	    }
#endif
	    msleep(100);

	    memset(cmd, 0, MAX_COMMAND_SIZE);
	    cmd[0] = TEST_UNIT_READY;

	    SRpnt = osst_do_scsi(SRpnt, STp, cmd, 0, DMA_NONE, STp->timeout, MAX_RETRIES, 1);
	}
	*aSRpnt = SRpnt;
#if DEBUG
	debugging = dbg;
#endif
	if ( STp->buffer->syscall_result &&
	     osst_write_error_recovery(STp, aSRpnt, 0) ) {
#if DEBUG
	    printk(OSST_DEB_MSG "%s:D: Abnormal exit from onstream wait ready\n", name);
	    printk(OSST_DEB_MSG "%s:D: Result = %d, Sense: 0=%02x, 2=%02x, 12=%02x, 13=%02x\n", name,
			STp->buffer->syscall_result, SRpnt->sense[0], SRpnt->sense[2],
			SRpnt->sense[12], SRpnt->sense[13]);
#endif
	    return (-EIO);
	}
#if DEBUG
	printk(OSST_DEB_MSG "%s:D: Normal exit from onstream wait ready\n", name);
#endif
	return 0;
}
