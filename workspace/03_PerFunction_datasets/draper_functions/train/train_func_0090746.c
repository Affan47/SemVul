est_set_ecode(int *ecp, int value, int line){
  char buf[ESTPATHBUFSIZ];
  assert(ecp && line > 0);
  *ecp = value;
  if(dpdbgfd >= 0){
    fflush(stdout);
    fflush(stderr);
    sprintf(buf, "* est_set_ecode: %d: [%d] %s\n", line, value, est_err_msg(value));
    write(dpdbgfd, buf, strlen(buf));
  }
}
