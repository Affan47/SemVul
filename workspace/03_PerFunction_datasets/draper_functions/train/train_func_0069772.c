checkmode(unsigned uid, unsigned gid,
		      unsigned mode, unsigned type)
{
  struct stat st;
  if (lstat(path.s, &st) == -1) {
    if (errno == ENOENT)
      error("does not exist");
    else
      diefsys(1, "{Could not stat '}s{'}", path.s);
  }
  else {
    if (uid != (unsigned)-1 && st.st_uid != uid)
      error("has wrong UID");
    if (gid != (unsigned)-1 && st.st_gid != gid)
      error("has wrong GID");
    if ((st.st_mode & 07777) != mode)
      error("has wrong permissions");
    if ((st.st_mode & ~07777) != type)
      error("is wrong file type");
  }
}
