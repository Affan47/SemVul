nxt_accel_get_tilt(nxt_t *nxt,int port,struct nxt_accel_vector *tilt) {
  char buf[3];

  if (nxt_i2c_read(nxt,port,nxt_accel_i2c_addr,NXT_ACCEL_REG_TILT,3,buf)!=3) {
    return -1;
  }

  if (tilt!=NULL) {
    tilt->x = buf[0];
    tilt->y = buf[1];
    tilt->z = buf[2];
  }

  return 0;
}
