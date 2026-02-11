pack_exchange(int i, double *buf)
{
  int m = 0;
  buf[m++] = shake_flag[i];
  int flag = shake_flag[i];
  if (flag == 1) {
    buf[m++] = shake_atom[i][0];
    buf[m++] = shake_atom[i][1];
    buf[m++] = shake_atom[i][2];
    buf[m++] = shake_type[i][0];
    buf[m++] = shake_type[i][1];
    buf[m++] = shake_type[i][2];
  } else if (flag == 2) {
    buf[m++] = shake_atom[i][0];
    buf[m++] = shake_atom[i][1];
    buf[m++] = shake_type[i][0];
  } else if (flag == 3) {
    buf[m++] = shake_atom[i][0];
    buf[m++] = shake_atom[i][1];
    buf[m++] = shake_atom[i][2];
    buf[m++] = shake_type[i][0];
    buf[m++] = shake_type[i][1];
  } else if (flag == 4) {
    buf[m++] = shake_atom[i][0];
    buf[m++] = shake_atom[i][1];
    buf[m++] = shake_atom[i][2];
    buf[m++] = shake_atom[i][3];
    buf[m++] = shake_type[i][0];
    buf[m++] = shake_type[i][1];
    buf[m++] = shake_type[i][2];
  }
  return m;
}
