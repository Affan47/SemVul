do_door_lock(struct osst_tape * STp, int do_lock)
{
	int retval;

#if DEBUG
	printk(OSST_DEB_MSG "%s:D: %socking drive door.\n", tape_name(STp), do_lock ? "L" : "Unl");
#endif

	retval = scsi_set_medium_removal(STp->device,
			do_lock ? SCSI_REMOVAL_PREVENT : SCSI_REMOVAL_ALLOW);
	if (!retval)
		STp->door_locked = do_lock ? ST_LOCKED_EXPLICIT : ST_UNLOCKED;
	else
		STp->door_locked = ST_LOCK_FAILS;
	return retval;
}
