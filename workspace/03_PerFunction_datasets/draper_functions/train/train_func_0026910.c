nxt_i2c_read_low(nxt_t *nxt,int port,int addr,size_t reg1,size_t nreg,void *buf) {
  time_t timeout;
  char cmd[3] = {
    addr,
    reg1
  };


  if (nreg>15) {
    nreg = 15;
  }

  nxt_ls_write(nxt,port,2,nreg,cmd);


  timeout = time(NULL)+2;
  while (nxt_ls_status(nxt,port)<((ssize_t)nreg) && time(NULL)<timeout);

  if (nxt_ls_read(nxt,port,nreg,buf)==-1) {
    return -1;
  }
  else {
    return nreg;
  }
}
