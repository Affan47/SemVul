ubknd(BW *bw)
{
	unsigned char **a;
	unsigned char *s;
        unsigned char *sh;

        if (!modify_logic(bw,bw->b))
        	return -1;

        sh=(unsigned char *)getenv("SHELL");

        if (file_exists(sh) && zcmp(sh,USTR "/bin/sh")) goto ok;
        if (file_exists(sh=USTR "/bin/bash")) goto ok;
        if (file_exists(sh=USTR "/usr/bin/bash")) goto ok;
        if (file_exists(sh=USTR "/bin/sh")) goto ok;

        msgnw(bw->parent, joe_gettext(_("\"SHELL\" environment variable not defined or exported")));
        return -1;

        ok:
	a = vamk(3);
	s = vsncpy(NULL, 0, sz(sh));
	a = vaadd(a, s);
	s = vsncpy(NULL, 0, sc("-i"));
	a = vaadd(a, s);
	return cstart(bw, sh, a, NULL, NULL, 0, 0);
}
