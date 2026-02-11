pfs_resolve_file_config( const char *filename )
{
	FILE *file;
	char line[PFS_LINE_MAX];
	char prefix[PFS_LINE_MAX];
	char redirect[PFS_LINE_MAX];
	int fields;
	int linenum=0;

	file = fopen(filename,"r");
	if(!file) fatal("couldn't open mountfile %s: %s\n",filename,strerror(errno));

	while(1) {
		if(!fgets(line,sizeof(line),file)) {
			if(errno==EINTR) {
				continue;
			} else {
				break;
			}
		}
		linenum++;
		if(line[0]=='#') continue;
		string_chomp(line);
		if(!line[0]) continue;
		fields = sscanf(line,"%s %s",prefix,redirect);

		if(fields==0) {
			continue;
		} else if(fields<2) {
			fatal("%s has an error on line %d\n",filename,linenum);
		} else {
			add_mount_entry(prefix,redirect);
		}
	}

	fclose(file);
}
