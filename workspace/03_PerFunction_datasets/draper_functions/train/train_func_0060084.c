generate_selfcert()
{
	const char *secrets_file;
	struct stat stb;

	secrets_file = lib->settings->get_str(lib->settings,
							"charon.plugins.stroke.secrets_file", SECRETS_FILE);


	if (stat(secrets_file, &stb) != 0)
	{
		mode_t oldmask;
		FILE *f;
		uid_t uid = 0;
		gid_t gid = 0;

#ifdef IPSEC_GROUP
		{
			char buf[1024];
			struct group group, *grp;

			if (getgrnam_r(IPSEC_GROUP, &group, buf, sizeof(buf), &grp) == 0 &&	grp)
			{
				gid = grp->gr_gid;
			}
		}
#endif
#ifdef IPSEC_USER
		{
			char buf[1024];
			struct passwd passwd, *pwp;

			if (getpwnam_r(IPSEC_USER, &passwd, buf, sizeof(buf), &pwp) == 0 &&	pwp)
			{
				uid = pwp->pw_uid;
			}
		}
#endif
		ignore_result(setegid(gid));
		ignore_result(seteuid(uid));
		ignore_result(system(IPSEC_SCRIPT " scepclient --out pkcs1 --out cert-self --quiet"));
		ignore_result(seteuid(0));
		ignore_result(setegid(0));


		oldmask = umask(0066);

		f = fopen(secrets_file, "w");
		if (f)
		{
			fprintf(f, "# /etc/ipsec.secrets - strongSwan IPsec secrets file\n");
			fprintf(f, "\n");
			fprintf(f, ": RSA myKey.der\n");
			fclose(f);
		}
		ignore_result(chown(secrets_file, uid, gid));
		umask(oldmask);
	}
}
