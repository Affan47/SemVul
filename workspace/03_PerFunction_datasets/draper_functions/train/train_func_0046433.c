fat_open(const char *filename, File_t *F, Volume_t *V, int flags) {
	int res;
	DWORD clus, off;

	if (filename == NULL) { fprintf(stderr,"fat_open(): invalid filename string\n"); return -1; }

	res = utf8_stricmp(filename,"");
	res = utf8_stricmp(filename,".");
	res |= utf8_stricmp(filename,"..");


	if ((res == 0)) {
		fprintf(stderr,"fat_open(): cannot open \".\" or \"..\" or an empty string. filename: %s\n", filename);
		return -1;
    }

	F->rootdir=0;
	F->V = V;

	res = utf8_stricmp(filename,"/");
	if (res == 0) {
		if (V->FatType == FAT32) {
			F->CurClus = 2;
		} else {
			F->CurClus = 1;
		}
		F->CurOff = F->CurAbsOff = 0;
		F->rootdir = 1;
		F->DirEntry = NULL;
		F->Mode = flags;
		return 0;
    }


    res = find_file(V, filename, F, &clus, &off);
	if (res != 0) {
		fprintf(stderr,"fat_open(): find file error fname: %s\n", filename);
		return -1;
	}

	F->DirEntryClus=clus;
	F->DirEntryOffset=off;

    memset(F->D.entry,0,21 * sizeof(LfnEntry_t));
	res = fetch_next_direntry(V, &(F->D), &clus, &off);
 	if (res <= 0) {
		perror("fat_open():"); return -1;
	} else  {
		F->DirEntry = (DirEntry_t *) &(F->D.entry[F->D.len - 1]);
		F->CurClus = get_fstclus(F->V,F->DirEntry);
		F->CurOff = F->CurAbsOff = 0;
		F->Mode = flags;
	}

	fprintf(stderr,"fat_open(%s): first cluster: %u, begins at %lld. direntry sz: %d:%d\n",filename, F->CurClus, byte_offset(V,F->CurClus, F->CurOff),res, F->D.len);
	return 0;
}
