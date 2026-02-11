ide_cd_expiry(ide_drive_t *drive)
{
	struct request *rq = drive->hwif->rq;
	unsigned long wait = 0;

	debug_log("%s: rq->cmd[0]: 0x%x\n", __func__, rq->cmd[0]);


	switch (rq->cmd[0]) {
	case GPCMD_BLANK:
	case GPCMD_FORMAT_UNIT:
	case GPCMD_RESERVE_RZONE_TRACK:
	case GPCMD_CLOSE_TRACK:
	case GPCMD_FLUSH_CACHE:
		wait = ATAPI_WAIT_PC;
		break;
	default:
		if (!(rq->cmd_flags & REQ_QUIET))
			printk(KERN_INFO PFX "cmd 0x%x timed out\n",
					 rq->cmd[0]);
		wait = 0;
		break;
	}
	return wait;
}
