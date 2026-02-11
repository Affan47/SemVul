DISK_examine_image (struct uae_prefs *p, int num, uae_u32 *crc32)
{
	int drvsec;
	int ret, i;
	drive *drv = &floppy[num];
	uae_u32 dos, crc, crc2;
	int wasdelayed = drv->dskchange_time;
	int sectable[MAX_SECTORS];
	int oldcyl, oldside;

	ret = 0;
	*crc32 = 0;
	oldcyl = drv->cyl;
	oldside = side;
	drv->cyl = 0;
	side = 0;
	if (!drive_insert (drv, p, num, p->floppyslots[num].df, true) || !drv->diskfile) {
		drv->cyl = oldcyl;
		side = oldside;
		return 1;
	}
	*crc32 = zfile_crc32 (drv->diskfile);
	decode_buffer (drv->bigmfmbuf, drv->cyl, 11, drv->ddhd, drv->filetype, &drvsec, sectable, 1);
	drv->cyl = oldcyl;
	side = oldside;
	if (sectable[0] == 0 || sectable[1] == 0) {
		ret = 2;
		goto end;
	}
	crc = crc2 = 0;
	for (i = 0; i < 1024; i += 4) {
		uae_u32 v = (writebuffer[i] << 24) | (writebuffer[i + 1] << 16) | (writebuffer[i + 2] << 8) | writebuffer[i + 3];
		if (i == 0)
			dos = v;
		if (i == 4) {
			crc2 = v;
			v = 0;
		}
		if (crc + v < crc)
			crc++;
		crc += v;
	}
	if (dos == 0x4b49434b) {
		ret = 10;
		goto end;
	}
	crc ^= 0xffffffff;
	if (crc != crc2) {
		ret = 3;
		goto end;
	}
	if (dos == 0x444f5300)
		ret = 10;
	else if (dos == 0x444f5301 || dos == 0x444f5302 || dos == 0x444f5303)
		ret = 11;
	else if (dos == 0x444f5304 || dos == 0x444f5305 || dos == 0x444f5306 || dos == 0x444f5307)
		ret = 12;
	else
		ret = 4;
end:
	drive_image_free (drv);
	if (wasdelayed > 1) {
		drive_eject (drv);
		currprefs.floppyslots[num].df[0] = 0;
		drv->dskchange_time = wasdelayed;
		disk_insert (num, drv->newname);
	}
	return ret;
}
