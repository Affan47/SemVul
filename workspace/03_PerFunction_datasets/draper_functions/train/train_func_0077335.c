fuse_kern_mount(const char *mountpoint, struct fuse_args *args)
{
	struct mount_opts mo;
	int res = -1;
	char *mnt_opts = NULL;

	memset(&mo, 0, sizeof(mo));
	mo.flags = MS_NOSUID | MS_NODEV;

	if (args &&
	    fuse_opt_parse(args, &mo, fuse_mount_opts, fuse_mount_opt_proc) == -1)
		return -1;

	if (mo.allow_other && mo.allow_root) {
		fprintf(stderr, "fuse: 'allow_other' and 'allow_root' options are mutually exclusive\n");
		goto out;
	}
	res = 0;
	if (mo.ishelp)
		goto out;

	res = -1;
	if (get_mnt_flag_opts(&mnt_opts, mo.flags) == -1)
		goto out;
	if (mo.kernel_opts && fuse_opt_add_opt(&mnt_opts, mo.kernel_opts) == -1)
		goto out;
	if (mo.mtab_opts &&  fuse_opt_add_opt(&mnt_opts, mo.mtab_opts) == -1)
		goto out;

	res = fuse_mount_sys(mountpoint, &mo, mnt_opts);
	if (res == -2) {
		if (mo.fusermount_opts &&
		    fuse_opt_add_opt(&mnt_opts, mo.fusermount_opts) == -1)
			goto out;

		if (mo.subtype) {
			char *tmp_opts = NULL;

			res = -1;
			if (fuse_opt_add_opt(&tmp_opts, mnt_opts) == -1 ||
			    fuse_opt_add_opt(&tmp_opts, mo.subtype_opt) == -1) {
				free(tmp_opts);
				goto out;
			}

			res = fuse_mount_fusermount(mountpoint, &mo, tmp_opts, 1);
			free(tmp_opts);
			if (res == -1)
				res = fuse_mount_fusermount(mountpoint, &mo,
							    mnt_opts, 0);
		} else {
			res = fuse_mount_fusermount(mountpoint, &mo, mnt_opts, 0);
		}
	}
out:
	free(mnt_opts);
	free(mo.fsname);
	free(mo.subtype);
	free(mo.fusermount_opts);
	free(mo.subtype_opt);
	free(mo.kernel_opts);
	free(mo.mtab_opts);
	return res;
}
