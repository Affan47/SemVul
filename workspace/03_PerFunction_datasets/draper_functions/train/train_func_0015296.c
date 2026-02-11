dminfo_show_deps(unsigned long table)
{
	int major, minor, count;
	unsigned long head, next, last, dev, bdev;
	char buf[BUFSIZE];


	GET_ADDR(table, dm_table, devices, head);

	fprintf(fp, "  %-3s  %-3s  %-16s  %-5s  %s\n",
		"MAJ", "MIN", "GENDISK", "COUNT", "DEVNAME");

	list_for_each (next, head, last) {

		GET_VALUE(next, dm_dev, count, count);
		GET_VALUE(next, dm_dev, bdev, bdev);
		GET_VALUE(bdev, block_device, bd_disk, dev);
		GET_VALUE(dev, gendisk, major, major);
		GET_VALUE(dev, gendisk, first_minor, minor);
		GET_STR(dev, gendisk, disk_name, buf, BUFSIZE);

		fprintf(fp, "  %-3d  %-3d  %-16lx  %-5d  %s\n",
			major, minor, dev, count, buf);
	}
}
