md_filetype(char *path, char *name) {

    char *fullpath;

    if (!strcmp(name,".") || !strcmp(name,"..")) return T_SKIP;
    fullpath=md_pconcat(0,path,name);
    if (lstat(fullpath,&filestat)<0) {
	error(0,ERR_STAT,fullpath);
	free(fullpath);
	return T_SKIP;
    }
    free(fullpath);
    if (filestat.st_ino==arcstat.st_ino) return T_SKIP;
    if (S_ISDIR(filestat.st_mode)) return T_DIR;
    if (S_ISREG(filestat.st_mode)) return T_REGULAR;
    return T_SPECIAL;
}
