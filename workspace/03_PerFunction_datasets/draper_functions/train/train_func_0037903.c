xbsd_initlabel (struct partition *p, struct xbsd_disklabel *d,
		int pindex __attribute__((__unused__))) {
	struct xbsd_partition *pp;
	struct geom g;

	get_geometry (fd, &g);
	memset (d, 0, sizeof (struct xbsd_disklabel));

	d -> d_magic = BSD_DISKMAGIC;

	if (strncmp (disk_device, "/dev/sd", 7) == 0)
		d -> d_type = BSD_DTYPE_SCSI;
	else
		d -> d_type = BSD_DTYPE_ST506;

#if 0
	d -> d_subtype = BSD_DSTYPE_INDOSPART & pindex;
#endif

#if !defined (__alpha__)
	d -> d_flags = BSD_D_DOSPART;
#else
	d -> d_flags = 0;
#endif
	d -> d_secsize = SECTOR_SIZE;
	d -> d_nsectors = g.sectors;
	d -> d_ntracks = g.heads;
	d -> d_ncylinders = g.cylinders;
	d -> d_secpercyl  = g.sectors * g.heads;
	if (d -> d_secpercyl == 0)
		d -> d_secpercyl = 1;
	d -> d_secperunit = d -> d_secpercyl * d -> d_ncylinders;

	d -> d_rpm = 3600;
	d -> d_interleave = 1;
	d -> d_trackskew = 0;
	d -> d_cylskew = 0;
	d -> d_headswitch = 0;
	d -> d_trkseek = 0;

	d -> d_magic2 = BSD_DISKMAGIC;
	d -> d_bbsize = BSD_BBSIZE;
	d -> d_sbsize = BSD_SBSIZE;

#if !defined (__alpha__)
	d -> d_npartitions = 4;
	pp = &d -> d_partitions[2];

	pp -> p_offset = get_start_sect(p);
	pp -> p_size   = get_nr_sects(p);
	pp -> p_fstype = BSD_FS_UNUSED;
	pp = &d -> d_partitions[3];

	pp -> p_offset = 0;
	pp -> p_size   = d -> d_secperunit;
	pp -> p_fstype = BSD_FS_UNUSED;
#elif defined (__alpha__)
	d -> d_npartitions = 3;
	pp = &d -> d_partitions[2];

	pp -> p_offset = 0;
	pp -> p_size   = d -> d_secperunit;
	pp -> p_fstype = BSD_FS_UNUSED;
#endif

	return 1;
}
