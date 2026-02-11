sftp_send_path(struct sftpjob *job, struct worker *w, const char *path) {
  if(protocol->encode(job, (char **)&path))
    fatal("cannot encode local path name '%s'", path);
  sftp_send_string(w, path);
}
