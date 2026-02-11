nxt_i2c_write_low(nxt_t *nxt,int port,int addr,size_t reg1,size_t nreg,void *buf) {
  char cmd[16] = {
    addr,
    reg1
  };

  if (nreg>14) {
    nreg = 14;
  }

  memcpy(cmd+2,buf,nreg);
  if (nxt_ls_write(nxt,port,nreg+2,0,cmd)==-1) {
    return -1;
  }
  else {
    return nreg;
  }
}
