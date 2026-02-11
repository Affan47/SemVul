sftp_v345_symlink(struct sftpjob *job) {
  char *targetpath, *linkpath;

  if(readonly)
    return SSH_FX_PERMISSION_DENIED;


  if(reverse_symlink) {
    pcheck(sftp_parse_path(job, &targetpath));
    pcheck(sftp_parse_path(job, &linkpath));
  } else {
    pcheck(sftp_parse_path(job, &linkpath));
    pcheck(sftp_parse_path(job, &targetpath));
  }
  D(("sftp_v345_symlink %s %s", targetpath, linkpath));
  if(symlink(targetpath, linkpath) < 0)
    return HANDLER_ERRNO;
  else
    return SSH_FX_OK;
}
