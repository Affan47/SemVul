_PLfuse_fgetattr(const char *file, struct stat *result,
                     struct fuse_file_info *fi) {
	int rv;
	FUSE_CONTEXT_PRE;
	DEBUGf("fgetattr begin: %s\n",file);
	ENTER;
	SAVETMPS;
	PUSHMARK(SP);
	XPUSHs(file ? sv_2mortal(newSVpv(file,0)) : &PL_sv_undef);
	XPUSHs(FH_GETHANDLE(fi));
	PUTBACK;
	rv = call_sv(MY_CXT.callback[34],G_ARRAY);
	SPAGAIN;
	if(rv != 13) {
		if(rv > 1) {
			fprintf(stderr,"inappropriate number of returned values from getattr\n");
			rv = -ENOSYS;
		} else if(rv)
			rv = POPi;
		else
			rv = -ENOENT;
	} else {
		result->st_blocks = POPi;
		result->st_blksize = POPi;
		PULL_TIME(result, st_ctim, POPs);
		PULL_TIME(result, st_mtim, POPs);
		PULL_TIME(result, st_atim, POPs);
		result->st_size = POPn;
		result->st_rdev = POPi;
		result->st_gid = POPi;
		result->st_uid = POPi;
		result->st_nlink = POPi;
		result->st_mode = POPi;
		result->st_ino   = POPi;
		result->st_dev = POPi;
		rv = 0;
	}
	FREETMPS;
	LEAVE;
	PUTBACK;
	DEBUGf("fgetattr end: %i\n",rv);
	FUSE_CONTEXT_POST;
	return rv;
}
