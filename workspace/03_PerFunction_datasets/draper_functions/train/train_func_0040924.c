crypt_verify(char *user, char *pass) {
#ifndef UNIXPW_CRYPT
	return 0;
#else
	struct passwd *pwd;
	char *realpw, *cr;
	int n;

	if (! scheck(user, 100, "username")) {
		return 0;
	}
	if (! scheck(pass, 100, "password")) {
		return 0;
	}
	if (! unixpw_list_match(user)) {
		return 0;
	}

	pwd = getpwnam(user);
	if (! pwd) {
		return 0;
	}

	realpw = pwd->pw_passwd;
	if (realpw == NULL || realpw[0] == '\0') {
		return 0;
	}

	if (db > 1) fprintf(stderr, "realpw='%s'\n", realpw);

	if (strlen(realpw) < 12) {

#if LIBVNCSERVER_HAVE_GETSPNAM
		struct spwd *sp = getspnam(user);
		if (sp != NULL && sp->sp_pwdp != NULL) {
			if (db) fprintf(stderr, "using getspnam()\n");
			realpw = sp->sp_pwdp;
		} else {
			if (db) fprintf(stderr, "skipping getspnam()\n");
		}
#endif
	}

	n = strlen(pass);
	if (pass[n-1] == '\n') {
		pass[n-1] = '\0';
	}


	cr = (char *) crypt(pass, realpw);
	if (db > 1) {
		fprintf(stderr, "user='%s' pass='%s' realpw='%s' cr='%s'\n",
		    user, pass, realpw, cr ? cr : "(null)");
	}
	if (cr == NULL || cr[0] == '\0') {
		return 0;
	}
	if (!strcmp(cr, realpw)) {
		return 1;
	} else {
		return 0;
	}
#endif
}
