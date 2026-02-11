get_nfs_mount_nr(void)
{
	FILE *fp;
	char line[8192];
	char type_name[10];
	unsigned int nfs = 0;

	if ((fp = fopen(NFSMOUNTSTATS, "r")) == NULL)

		return 0;

	while (fgets(line, 8192, fp) != NULL) {

		if ((strstr(line, "mounted")) && (strstr(line, "on")) &&
		    (strstr(line, "with")) && (strstr(line, "fstype"))) {

			sscanf(strstr(line, "fstype") + 6, "%9s", type_name);
			if ((!strncmp(type_name, "nfs", 3)) && (strncmp(type_name, "nfsd", 4))) {
				nfs ++;
			}
		}
	}

	fclose(fp);

	return nfs;
}
