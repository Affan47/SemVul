play_ioctl (int unitnum, int startlsn, int endlsn, int scan, play_status_callback statusfunc, play_subchannel_callback subfunc)
{
    struct scsidevdata *sdd = unitisopen(unitnum);
    DEBUG_LOG ("SCSIDEV: unit = %d, play_ioctl\n", unitnum);
    if (sdd) {
        int err;
        struct cdrom_msf msf;
        startlsn += 150;
        endlsn += 150;
        msf.cdmsf_min0 = (startlsn / 75) / 60;
        msf.cdmsf_sec0 = (startlsn / 75) % 60;
        msf.cdmsf_frame0 = (startlsn % 75);
        msf.cdmsf_min1 = (endlsn / 75) / 60;
        msf.cdmsf_sec1 = (endlsn / 75) % 60;
        msf.cdmsf_frame1 = (endlsn % 75);
        err = ioctl(sdd->fd, CDROMPLAYMSF, (long)&msf);
        DEBUG_LOG("SCSIDEV: err %d, errno %d\n", err, errno);
        return (err >= 0) ? 1 : 0;
    }
    return -1;
}
