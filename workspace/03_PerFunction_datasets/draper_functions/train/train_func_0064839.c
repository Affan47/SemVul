loop_findfree(char *buff, size_t buffsz)
{   unsigned idx, found = 0;
    int devfd, devno;
    struct loop_info64 linfo;
    char loopname[256] = "";
    struct stat sbuff;

#ifdef LOOP_CTL_GET_FREE
    devfd = open("/dev/loop-control", O_RDWR);
    devno = ioctl(devfd, LOOP_CTL_GET_FREE);
    close(devfd);
    if (devfd >=0 && devno >= 0) {
        snprintf(loopname, sizeof(loopname), "/dev/loop%d", devno);
        found = 1;
    }
#endif

    for (devno=0; devno<256 && !found; ++devno) {
        for (idx=0; loop_formats[idx]!=NULL && !found; ++idx) {
            snprintf(loopname, sizeof(loopname),
                     loop_formats[idx], (unsigned)devno);
            if (stat(loopname, &sbuff) || !S_ISBLK(sbuff.st_mode)) continue;
            devfd = open(loopname, O_RDONLY);
            if (devfd < 0) continue;
            if (ioctl(devfd, LOOP_GET_STATUS64, &linfo) && errno == ENXIO) {
                found = 1;
            }
            close(devfd);
        }
    }

    if (found && buff != NULL) strncpy(buff, loopname, buffsz);

    return !found;
}
