afArchiveOwner (archDirSym, writeok, gid)
     char    *archDirSym;
     bool    *writeok;
     gid_t   *gid;
{
  struct stat ibuf;

  *writeok = FALSE;
  *gid = -1;

  if (archDirSym == curAtFSPath) {
    *writeok = curAtFSWriteOk;
    *gid = curAtFSgid;
    return (af_afuser (curAtFSuid));
  }

  if (stat (archDirSym, &ibuf) == ERROR) {
    curAtFSPath = NULL;
    curAtFSuid = -1;
    curAtFSgid = -1;
    curAtFSWriteOk = FALSE;
    curAtFSMode = 0;
    return (NULL);
  }

  if (!access (archDirSym, W_OK))
    *writeok = TRUE;

  curAtFSPath = archDirSym;
  curAtFSuid = ibuf.st_uid;
  *gid = curAtFSgid = ibuf.st_gid;
  curAtFSWriteOk = *writeok;
  curAtFSMode = ibuf.st_mode;

  return (af_afuser (ibuf.st_uid));
}
