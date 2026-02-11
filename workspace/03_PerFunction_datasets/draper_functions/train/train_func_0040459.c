format_root(Fs_t *Fs, char *label, union bootsector *boot)
{
	Stream_t *RootDir;
	char *buf;
	int i;
	struct ClashHandling_t ch;
	int dirlen;

	init_clash_handling(&ch);
	ch.name_converter = label_name_uc;
	ch.ignore_entry = -2;

	buf = safe_malloc(Fs->sector_size);
	RootDir = OpenRoot((Stream_t *)Fs);
	if(!RootDir){
		fprintf(stderr,"Could not open root directory\n");
		exit(1);
	}

	memset(buf, '\0', Fs->sector_size);

	if(Fs->fat_bits == 32) {


		dirlen = Fs->cluster_size;
		fatAllocate(Fs, Fs->rootCluster, Fs->end_fat);
	} else
		dirlen = Fs->dir_len;
	for (i = 0; i < dirlen; i++)
		WRITES(RootDir, buf, sectorsToBytes((Stream_t*)Fs, i),
			   Fs->sector_size);

	ch.ignore_entry = 1;
	if(label[0])
		mwrite_one(RootDir,label, 0, labelit, NULL,&ch);

	FREE(&RootDir);
	if(Fs->fat_bits == 32)
		set_word(boot->boot.dirents, 0);
	else
		set_word(boot->boot.dirents, Fs->dir_len * (Fs->sector_size / 32));
	free(buf);
}
