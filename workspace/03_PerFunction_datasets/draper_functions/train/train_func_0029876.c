detect_odd_sci01(int fh)
{
    byte buf[6];
    int files_ok = 1;
    int fsize, resources_nr, tempfh, read_ok;
    char filename[14];

    if ((fsize = sci_fd_size(fh)) < 0) {
	perror("Error occured while trying to get filesize of resource.map");
	return SCI_ERROR_RESMAP_NOT_FOUND;
    }

    resources_nr = fsize / SCI0_RESMAP_ENTRIES_SIZE;

    while (resources_nr-->1)
    {
        read_ok = read(fh, &buf, SCI0_RESMAP_ENTRIES_SIZE);

	if (read_ok)
	{
		sprintf(filename, "resource.%03i", SCI0_RESFILE_GET_FILE(buf+2));
		tempfh = sci_open(filename, O_RDONLY | O_BINARY);

		if (tempfh == SCI_INVALID_FD) {
			files_ok = 0;
			break;
		}

		close(tempfh);
	}
    }

    lseek(fh, 0, SEEK_SET);

    return files_ok;
}
