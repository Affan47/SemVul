setmodes(const char* filename,
		     unsigned uid, unsigned gid, unsigned mode)
{
  if (chown(filename, uid, gid) == -1)
    diefsys(1, "{Could not set owner or group for }s", filename);
  if (chmod(filename, mode) == -1)
    diefsys(1, "{Could not set mode for }s", filename);
}
