fusefat_truncate(const char *path, off_t size) {
    int res;
	File_t F;
	Volume_t *V;
	fusefat_getvolume(V);
	fprintf(stderr,"truncate(%s, %d)\n",path,(int) size);
	fat_lock(V);
    if ((res =  fat_open(path, &F, V, O_RDWR)) != 0) { fat_unlock(V); fprintf(stderr,"-- %d",__LINE__); return -ENOENT; }
    if ((res =  fat_truncate(&F, size)) != 0) { fat_unlock(V); fprintf(stderr,"-- %d",__LINE__); return -1; }
	fat_unlock(V);
    return 0;
}
