_dosopendev(drive)
int drive;
{
	devstat dev;
	int i, new, drv;

	if (!drive) {
		doserrno = ENODEV;
		return(-1);
	}
	for (new = 0; new < maxdev; new++) if (!(devlist[new].drive)) break;
	if (new >= DOSNOFILE || maxorder >= DOSNOFILE) {
		doserrno = EMFILE;
		return(-1);
	}
	drv = Xtoupper(drive);

	for (i = maxorder - 1; i >= 0; i--)
		if (drv == (int)devlist[devorder[i]].drive) break;
	if (i >= 0) {
		memcpy((char *)&dev,
			(char *)&(devlist[devorder[i]]), sizeof(dev));
		dev.flags |= F_DUPL;
		dev.flags &= ~(F_CACHE | F_WRFAT);
	}
	else {
		if (readbpb(&dev, drv) < 0) return(-1);
		dev.dircache = NULL;
		if (readfat(&dev) < 0) {
#if	!MSDOS
			VOID_C close(dev.fd);
#endif
			return(-1);
		}
	}
	if (Xislower(drive)) dev.flags |= F_LFN;
	else dev.flags &= ~F_LFN;

	memcpy((char *)&(devlist[new]), (char *)&dev, sizeof(*devlist));
	devlist[new].nlink = 1;
	if (new >= maxdev) maxdev++;
	devorder[maxorder++] = new;

	return(new);
}
