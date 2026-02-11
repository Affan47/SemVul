sgi_set_partition(int i, unsigned int start, unsigned int length, int sys) {
	sgilabel->partitions[i].id = SSWAP32(sys);
	sgilabel->partitions[i].num_sectors = SSWAP32(length);
	sgilabel->partitions[i].start_sector = SSWAP32(start);
	set_changed(i);
	if (sgi_gaps() < 0)
		printf(_("Do You know, You got a partition overlap on the disk?\n"));
}
