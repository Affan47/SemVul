open_file(int mode)
{
	char	*fname = envprocess(SPUFILE);
	struct	stat	pwbuf;

	if  ((spuf_fid = open(fname, mode)) < 0)  {
		if  (errno == EACCES)  {
			print_error(8000);
			exit(E_SETUP);
		}
		if  (errno == ENOENT)
			init_file(fname);
		spuf_fid = open(fname, mode);
	}

	if  (spuf_fid < 0)  {
		print_error(8002);
		exit(E_SETUP);
	}

	fcntl(spuf_fid, F_SETFD, 1);
	lockit(spuf_fid, F_RDLCK);
	read(spuf_fid, (char *)&Spuhdr, sizeof(Spuhdr));


	if  (Spuhdr.sph_version != GNU_SPOOL_MAJOR_VERSION)  {
		disp_arg[0] = Spuhdr.sph_version;
		disp_arg[1] = GNU_SPOOL_MAJOR_VERSION;
		print_error(8007);
	}

	if  (stat("/etc/passwd", &pwbuf) < 0)  {
		free(fname);
		return;
	}

	unlockit(spuf_fid);
	free(fname);

	if  (Spuhdr.sph_lastp >= pwbuf.st_mtime)  {
		if  (Spuhdr.sph_lastp > pwbuf.st_mtime)
			print_error(8003);
		spu_needs_rebuild = 0;
		return;
	}
	spu_needs_rebuild = 1;
}
