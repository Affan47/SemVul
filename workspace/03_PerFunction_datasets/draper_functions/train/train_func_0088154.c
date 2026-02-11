nsfromdisplay(void)
{
	int fd;
	Dir *d;
	char *disp, *p;

	if((disp = getenv("DISPLAY")) == nil){
#ifdef __APPLE__

		disp = strdup(":0.0");
		if(disp == nil)
			return nil;
#else
		werrstr("$DISPLAY not set");
		return nil;
#endif
	}


	p = strrchr(disp, ':');
	if(p){
		p++;
		while(isdigit((uchar)*p))
			p++;
		if(strcmp(p, ".0") == 0)
			*p = 0;
	}


	for(p=disp; *p; p++)
		if(*p == '/')
			*p = '_';

	p = smprint("/tmp/ns.%s.%s", getuser(), disp);
	free(disp);
	if(p == nil){
		werrstr("out of memory");
		return p;
	}
	if((fd=create(p, OREAD, DMDIR|0700)) >= 0){
		close(fd);
		return p;
	}
	if((d = dirstat(p)) == nil){
		free(d);
		werrstr("stat %s: %r", p);
		free(p);
		return nil;
	}
	if((d->mode&0777) != 0700 || !isme(d->uid)){
		werrstr("bad name space dir %s", p);
		free(p);
		free(d);
		return nil;
	}
	free(d);
	return p;
}
