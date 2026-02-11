getVersion() {
	char file[0x100], *p;
	DWORD ver;
	strcpy(file, dataFile);
	if ((p=strrchr(file, '/')+1) == (void *)1)
		p = file;
	strcpy(p, "8021x.exe");
	if ((ver=getVer(file)) == (DWORD)-1)
		return -1;
	p = (char *)&ver;
	version[0] = p[2];
	version[1] = p[0];
	bufType = 1;
	return 0;
}
