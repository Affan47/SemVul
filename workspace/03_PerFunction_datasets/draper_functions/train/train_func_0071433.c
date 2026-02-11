renameit(dos_name_t *dosname,
		    char *longname,
		    void *arg0,
		    direntry_t *targetEntry)
{
	Arg_t *arg = (Arg_t *) arg0;
	int fat;

	targetEntry->dir = arg->entry->dir;
	dosnameToDirentry(dosname, &targetEntry->dir);

	if(IS_DIR(targetEntry)) {
		direntry_t *movedEntry;


		movedEntry = getDirentry(arg->mp.File);
		if(movedEntry->Dir != targetEntry->Dir) {

			direntry_t subEntry;
			Stream_t *oldDir;


			initializeDirentry(&subEntry, arg->mp.File);

			switch(vfat_lookup(&subEntry, "..", 2, ACCEPT_DIR,
					   NULL, NULL)) {
			    case -1:
				fprintf(stderr,
					" Directory has no parent entry\n");
				break;
			    case -2:
				return ERROR_ONE;
			    case 0:
				GET_DATA(targetEntry->Dir, 0, 0, 0, &fat);
				if (fat == fat32RootCluster(targetEntry->Dir)) {
				    fat = 0;
				}

				subEntry.dir.start[1] = (fat >> 8) & 0xff;
				subEntry.dir.start[0] = fat & 0xff;
				dir_write(&subEntry);
				if(arg->verbose){
					fprintf(stderr,
						"Easy, isn't it? I wonder why DOS can't do this.\n");
				}
				break;
			}

			wipeEntry(movedEntry);


			oldDir = movedEntry->Dir;
			*movedEntry = *targetEntry;
			COPY(targetEntry->Dir);
			FREE(&oldDir);
			return 0;
		}
	}


	wipeEntry(arg->mp.direntry);
	return 0;
}
