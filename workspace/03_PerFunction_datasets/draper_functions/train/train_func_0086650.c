close_device (int unitnum)
{
    struct scsidevdata *sdd = &drives[unitnum];

    DEBUG_LOG ("SCSIDEV: unit = %d: close_device\n", unitnum);
    if (sdd->fd != -1) {
	close (sdd->fd);
	sdd->fd = -1;
    }
}
