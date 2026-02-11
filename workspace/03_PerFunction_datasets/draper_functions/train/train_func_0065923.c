hout3i (gaint cmd, gaint i1, gaint i2, gaint i3) {

  if (bflag||herr) return;
  *hpnt = cmd;
  hpnt++;
  *hpnt = i1;
  hpnt++;
  *hpnt = i2;
  hpnt++;
  *hpnt = i3;
  hpnt++;
  if (hpnt>hend) hfull();
}
