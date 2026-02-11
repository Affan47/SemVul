nxt_get_sensor(nxt_t *nxt,int sensor) {
  struct nxt_sensor_values values;
  if (nxt_get_sensor_values(nxt,sensor,&values)==0) {
    return values.is_calibrated?values.calibrated:values.scaled;
  }
  else {
    return -1;
  }
}
