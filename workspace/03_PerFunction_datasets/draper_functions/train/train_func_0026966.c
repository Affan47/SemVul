partlist_getinfo(char *bufdat, int bufsize, struct s_devinfo *blkdev, int item)
{
    memset(bufdat, 0, bufsize);
    switch (item)
    {
        case 0:    snprintf(bufdat, bufsize, "%s", blkdev->devname); break;
        case 1:    snprintf(bufdat, bufsize, "%s", blkdev->fsname); break;
        case 2:    snprintf(bufdat, bufsize, "%s", blkdev->label); break;
        case 3:    snprintf(bufdat, bufsize, "%s", blkdev->txtsize); break;
        case 4:    snprintf(bufdat, bufsize, "%d", blkdev->major); break;
        case 5:    snprintf(bufdat, bufsize, "%d", blkdev->minor); break;
        case 6:    snprintf(bufdat, bufsize, "%s", blkdev->longname); break;
        case 7:    snprintf(bufdat, bufsize, "%s", blkdev->uuid); break;
    };
    return bufdat;
}
