ide_cd_lockdoor(ide_drive_t *drive, int lockflag,
		    struct request_sense *sense)
{
	struct request_sense my_sense;
	int stat;

	if (sense == NULL)
		sense = &my_sense;


	if ((drive->dev_flags & IDE_DFLAG_DOORLOCKING) == 0) {
		stat = 0;
	} else {
		unsigned char cmd[BLK_MAX_CDB];

		memset(cmd, 0, BLK_MAX_CDB);

		cmd[0] = GPCMD_PREVENT_ALLOW_MEDIUM_REMOVAL;
		cmd[4] = lockflag ? 1 : 0;

		stat = ide_cd_queue_pc(drive, cmd, 0, NULL, NULL,
				       sense, 0, 0);
	}


	if (stat != 0 &&
	    sense->sense_key == ILLEGAL_REQUEST &&
	    (sense->asc == 0x24 || sense->asc == 0x20)) {
		printk(KERN_ERR "%s: door locking not supported\n",
			drive->name);
		drive->dev_flags &= ~IDE_DFLAG_DOORLOCKING;
		stat = 0;
	}


	if (stat != 0 && sense->sense_key == NOT_READY && sense->asc == 0x3a)
		stat = 0;

	if (stat == 0) {
		if (lockflag)
			drive->atapi_flags |= IDE_AFLAG_DOOR_LOCKED;
		else
			drive->atapi_flags &= ~IDE_AFLAG_DOOR_LOCKED;
	}

	return stat;
}
