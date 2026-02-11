ftp_delete(struct FTP *ctrl_con, const char *path)
{
  int status;
  put_cmd(ctrl_con, "DELE", path);
  status = read_status(ctrl_con);
  if (verbose) {
    printf("Got %d from DELE comamnd\n", status);
  }
  return status_map(status);
}
