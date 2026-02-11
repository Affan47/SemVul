get_encodings(void)
{
	int y, x;
	unsigned char **encodings = 0;
	unsigned char **t;
	unsigned char *r;
	unsigned char *oldpwd = pwd();
	unsigned char *p;
	unsigned char buf[1024];


	r = vsncpy(NULL,0,sc("utf-8"));
	encodings = vaadd(encodings, r);

	for (y=0; y!=sizeof(builtin_charmaps)/sizeof(struct builtin_charmap); ++y) {
		r = vsncpy(NULL,0,sz(builtin_charmaps[y].name));
		encodings = vaadd(encodings, r);
	}


	for (y=0; alias_table[y].alias; ++y) {
		r = vsncpy(NULL,0,sz(alias_table[y].alias));
		encodings = vaadd(encodings, r);
	}


	p = (unsigned char *)getenv("HOME");
	if (p) {
		joe_snprintf_1((char *)buf,sizeof(buf),"%s/.joe/charmaps",p);
		if (!chpwd(buf) && (t = rexpnd(US "*"))) {
			for (x = 0; x != aLEN(t); ++x)
				if (strcmp(t[x],"..")) {
					for (y = 0; y != aLEN(encodings); ++y)
						if (!strcmp(t[x],encodings[y]))
							break;
					if (y == aLEN(encodings)) {
						r = vsncpy(NULL,0,sv(t[x]));
						encodings = vaadd(encodings,r);
					}
				}
			varm(t);
		}
	}

	if (!chpwd(US (JOERC "charmaps")) && (t = rexpnd(US "*"))) {
		for (x = 0; x != aLEN(t); ++x)
			if (strcmp(t[x],"..")) {
				for (y = 0; y != aLEN(encodings); ++y)
					if (!strcmp(t[x],encodings[y]))
						break;
				if (y == aLEN(encodings)) {
					r = vsncpy(NULL,0,sv(t[x]));
					encodings = vaadd(encodings,r);
				}
			}
		varm(t);
	}

	chpwd(oldpwd);

	return encodings;
}
