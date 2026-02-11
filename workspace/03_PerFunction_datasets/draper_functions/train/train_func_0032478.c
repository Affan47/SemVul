my_addmntent (mntFILE *mfp, struct my_mntent *mnt) {
	char *m1, *m2, *m3, *m4;
	int res;

	if (fseek (mfp->mntent_fp, 0, SEEK_END))
		return 1;

	m1 = mangle(mnt->mnt_fsname);
	m2 = mangle(mnt->mnt_dir);
	m3 = mangle(mnt->mnt_type);
	m4 = mnt->mnt_opts ? mangle(mnt->mnt_opts) : "rw";

	res = fprintf (mfp->mntent_fp, "%s %s %s %s %d %d\n",
		       m1, m2, m3, m4, mnt->mnt_freq, mnt->mnt_passno);

	free(m1);
	free(m2);
	free(m3);
	if (mnt->mnt_opts)
		free(m4);
	return (res < 0) ? 1 : 0;
}
