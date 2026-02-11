write_behind_check(struct scsi_tape * STp)
{
	int retval = 0;
	struct st_buffer *STbuffer;
	struct st_partstat *STps;
	struct st_cmdstatus *cmdstatp;
	struct st_request *SRpnt;

	STbuffer = STp->buffer;
	if (!STbuffer->writing)
		return 0;

	DEB(
	if (STp->write_pending)
		STp->nbr_waits++;
	else
		STp->nbr_finished++;
	)

	wait_for_completion(&(STp->wait));
	SRpnt = STbuffer->last_SRpnt;
	STbuffer->last_SRpnt = NULL;
	SRpnt->waiting = NULL;

	(STp->buffer)->syscall_result = st_chk_result(STp, SRpnt);
	st_release_request(SRpnt);

	STbuffer->buffer_bytes -= STbuffer->writing;
	STps = &(STp->ps[STp->partition]);
	if (STps->drv_block >= 0) {
		if (STp->block_size == 0)
			STps->drv_block++;
		else
			STps->drv_block += STbuffer->writing / STp->block_size;
	}

	cmdstatp = &STbuffer->cmdstat;
	if (STbuffer->syscall_result) {
		retval = -EIO;
		if (cmdstatp->have_sense && !cmdstatp->deferred &&
		    (cmdstatp->flags & SENSE_EOM) &&
		    (cmdstatp->sense_hdr.sense_key == NO_SENSE ||
		     cmdstatp->sense_hdr.sense_key == RECOVERED_ERROR)) {

			if (!cmdstatp->remainder_valid ||
			    cmdstatp->uremainder64 == 0)
				retval = -ENOSPC;
		}
		if (retval == -EIO)
			STps->drv_block = -1;
	}
	STbuffer->writing = 0;

	DEB(if (debugging && retval)
		    st_printk(ST_DEB_MSG, STp,
				"Async write error %x, return value %d.\n",
				STbuffer->cmdstat.midlevel_result, retval);)

	return retval;
}
