scsi_partsize(unsigned char *buf, unsigned long capacity,
	       unsigned int *cyls, unsigned int *hds, unsigned int *secs)
{
	struct partition *p = (struct partition *)buf, *largest = NULL;
	int i, largest_cyl;
	int cyl, ext_cyl, end_head, end_cyl, end_sector;
	unsigned int logical_end, physical_end, ext_physical_end;


	if (*(unsigned short *) (buf + 64) == 0xAA55) {
		for (largest_cyl = -1, i = 0; i < 4; ++i, ++p) {
			if (!p->sys_ind)
				continue;
#ifdef DEBUG
			printk("scsicam_bios_param : partition %d has system \n",
			       i);
#endif
			cyl = p->cyl + ((p->sector & 0xc0) << 2);
			if (cyl > largest_cyl) {
				largest_cyl = cyl;
				largest = p;
			}
		}
	}
	if (largest) {
		end_cyl = largest->end_cyl + ((largest->end_sector & 0xc0) << 2);
		end_head = largest->end_head;
		end_sector = largest->end_sector & 0x3f;

		if (end_head + 1 == 0 || end_sector == 0)
			return -1;

#ifdef DEBUG
		printk("scsicam_bios_param : end at h = %d, c = %d, s = %d\n",
		       end_head, end_cyl, end_sector);
#endif

		physical_end = end_cyl * (end_head + 1) * end_sector +
		    end_head * end_sector + end_sector;


		logical_end = get_unaligned_le32(&largest->start_sect)
		    + get_unaligned_le32(&largest->nr_sects);


		ext_cyl = (logical_end - (end_head * end_sector + end_sector))
		    / (end_head + 1) / end_sector;
		ext_physical_end = ext_cyl * (end_head + 1) * end_sector +
		    end_head * end_sector + end_sector;

#ifdef DEBUG
		printk("scsicam_bios_param : logical_end=%d physical_end=%d ext_physical_end=%d ext_cyl=%d\n"
		  ,logical_end, physical_end, ext_physical_end, ext_cyl);
#endif

		if ((logical_end == physical_end) ||
		  (end_cyl == 1023 && ext_physical_end == logical_end)) {
			*secs = end_sector;
			*hds = end_head + 1;
			*cyls = capacity / ((end_head + 1) * end_sector);
			return 0;
		}
#ifdef DEBUG
		printk("scsicam_bios_param : logical (%u) != physical (%u)\n",
		       logical_end, physical_end);
#endif
	}
	return -1;
}
