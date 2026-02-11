get_filesys_unitconfig (struct uae_prefs *p, int index, struct mountedinfo *mi)
{
	UnitInfo *ui = getuip (p, index);
	struct uaedev_config_info *uci = &p->mountconfig[index];
	UnitInfo uitmp;

	memset (mi, 0, sizeof (struct mountedinfo));
	memset (&uitmp, 0, sizeof uitmp);
	if (!ui) {
		ui = &uitmp;
		if (!uci->ishdf) {
			mi->ismounted = 1;
			if (uci->rootdir && _tcslen (uci->rootdir) == 0)
				return FILESYS_VIRTUAL;
			if (my_existsfile (uci->rootdir)) {
				mi->ismedia = 1;
				return FILESYS_VIRTUAL;
			}
			if (my_getvolumeinfo (uci->rootdir) < 0)
				return -1;
			mi->ismedia = true;
			return FILESYS_VIRTUAL;
		} else {
			ui->hf.readonly = true;
			ui->hf.blocksize = uci->blocksize;
			if (!hdf_open (&ui->hf, uci->rootdir)) {
				mi->ismedia = false;
				mi->ismounted = true;
				if (uci->reserved == 0 && uci->sectors == 0 && uci->surfaces == 0) {
					if (ui->hf.flags & 1)
						return FILESYS_HARDDRIVE;
					return FILESYS_HARDFILE_RDB;
				}
				return -1;
			}
			mi->ismedia = true;
			if (ui->hf.drive_empty)
				mi->ismedia = 0;
			hdf_close (&ui->hf);
		}
	} else {
		if (!ui->controller || (ui->controller && p->cs_ide)) {
			mi->ismounted = 1;
			if (uci->ishdf)
				mi->ismedia = ui->hf.drive_empty ? false : true;
			else
				mi->ismedia = true;
		}
	}
	mi->size = ui->hf.virtsize;
	if (uci->cyls) {
		mi->nrcyls = uci->cyls;
	} else {
		mi->nrcyls = (int)(uci->sectors * uci->surfaces ? (ui->hf.virtsize / uci->blocksize) / (uci->sectors * uci->surfaces) : 0);
	}
	if (!uci->ishdf)
		return FILESYS_VIRTUAL;
	if (uci->reserved == 0 && uci->sectors == 0 && uci->surfaces == 0) {
		if (ui->hf.flags & 1)
			return FILESYS_HARDDRIVE;
		return FILESYS_HARDFILE_RDB;
	}
	return FILESYS_HARDFILE;
}
