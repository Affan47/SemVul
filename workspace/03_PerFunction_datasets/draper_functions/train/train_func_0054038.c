ide_cd_do_request(ide_drive_t *drive, struct request *rq,
					sector_t block)
{
	struct ide_cmd cmd;
	int uptodate = 0;
	unsigned int nsectors;

	ide_debug_log(IDE_DBG_RQ, "cmd: 0x%x, block: %llu",
				  rq->cmd[0], (unsigned long long)block);

	if (drive->debug_mask & IDE_DBG_RQ)
		blk_dump_rq_flags(rq, "ide_cd_do_request");

	switch (rq->cmd_type) {
	case REQ_TYPE_FS:
		if (cdrom_start_rw(drive, rq) == ide_stopped)
			goto out_end;
		break;
	case REQ_TYPE_ATA_SENSE:
	case REQ_TYPE_BLOCK_PC:
	case REQ_TYPE_ATA_PC:
		if (!rq->timeout)
			rq->timeout = ATAPI_WAIT_PC;

		cdrom_do_block_pc(drive, rq);
		break;
	case REQ_TYPE_DRV_PRIV:

		uptodate = 1;
		goto out_end;
	default:
		BUG();
	}


	ide_prep_sense(drive, rq);

	memset(&cmd, 0, sizeof(cmd));

	if (rq_data_dir(rq))
		cmd.tf_flags |= IDE_TFLAG_WRITE;

	cmd.rq = rq;

	if (rq->cmd_type == REQ_TYPE_FS || blk_rq_bytes(rq)) {
		ide_init_sg_cmd(&cmd, blk_rq_bytes(rq));
		ide_map_sg(drive, &cmd);
	}

	return ide_issue_pc(drive, &cmd);
out_end:
	nsectors = blk_rq_sectors(rq);

	if (nsectors == 0)
		nsectors = 1;

	ide_complete_rq(drive, uptodate ? 0 : -EIO, nsectors << 9);

	return ide_stopped;
}
