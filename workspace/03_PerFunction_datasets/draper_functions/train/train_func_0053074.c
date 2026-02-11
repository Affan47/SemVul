__addmntent (FILE *stream, const struct mntent *mnt)
{
  struct mntent mntcopy = *mnt;
  if (fseek (stream, 0, SEEK_END))
    return 1;


  encode_name (mntcopy.mnt_fsname);
  encode_name (mntcopy.mnt_dir);
  encode_name (mntcopy.mnt_type);
  encode_name (mntcopy.mnt_opts);

  return (fprintf (stream, "%s %s %s %s %d %d\n",
		   mntcopy.mnt_fsname,
		   mntcopy.mnt_dir,
		   mntcopy.mnt_type,
		   mntcopy.mnt_opts,
		   mntcopy.mnt_freq,
		   mntcopy.mnt_passno) < 0
	  || fflush (stream) != 0);
}
