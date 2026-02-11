gar_load_fat(struct gimg *g, int dataoffset, int blocksize, unsigned int fatoffset)
{
	struct FATblock_t fent;
	ssize_t s = sizeof(struct FATblock_t);
	int count = 0;
	int rc, rsz = 0;
	struct fat_entry *fe;
	int userootdir = 0;
	int fatend = dataoffset;
	int seendot = 0;

	if (!fatend) {
		log(15, "FAT Will use size from rootdir\n");
		userootdir = 1;
	} else {
		fatend -= sizeof(struct hdr_img_t);
		log(15, "FAT size %d\n", fatend);
	}

	if (fatoffset) {
		log(14, "FAT offset: %d\n", fatoffset);
		glseek(g, fatoffset * 512, SEEK_SET);
	}

	while ((rc = gread(g, &fent, s)) == s) {
		if (fent.flag != 0x00)
			break;
		rsz+=rc;
		count ++;
	}
	log(17, "FAT Reserved entries %d(%ld)\n", count, s);
	count = 0;
	do {
		rsz+=rc;
		if(fent.flag != 0x01 && !fatend)
			break;
		if(fent.flag != 0x01 && fatend) {
			if (fatend && rsz>=fatend)
				break;
			continue;
		}
		if (!seendot||(userootdir && !fatend)) {
			if (fent.name[0] == ' ' && fent.type[0] == ' ') {
				fatend = fent.size - s;
				seendot = 1;
			}
		}
		gar_add_fe(g, &fent, blocksize);
		count ++;
		if (fatend && rsz>=fatend)
			break;
	} while ((rc = gread(g, &fent, s)) == s);

	if (!count) {
		log(1, "Failed to read FAT\n");
		return 0;
	}
	log(10, "FAT Directory %d entries %d bytes\n", count, rsz);
	list_for_entry(fe, &g->lfatfiles, l) {
		log(10,"%s %ld\n",fe->filename,fe->size);
	}

	if (userootdir) {
		dataoffset = fatend + sizeof(struct hdr_img_t);
		log(15, "FAT DataOffset corrected to %d\n", dataoffset);
	}

	return count * s;
}
