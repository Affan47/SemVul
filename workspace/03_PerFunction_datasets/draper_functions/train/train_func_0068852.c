g2sp (gribfield *gfld) {
  gaint sp;
  sp = -999;
  if (gfld->ipdtnum ==  8) sp = gfld->ipdtmpl[23];
  if (gfld->ipdtnum ==  9) sp = gfld->ipdtmpl[30];
  if (gfld->ipdtnum == 10) sp = gfld->ipdtmpl[24];
  if (gfld->ipdtnum == 11) sp = gfld->ipdtmpl[26];
  if (gfld->ipdtnum == 12) sp = gfld->ipdtmpl[25];
  if (gfld->ipdtnum == 15) sp = gfld->ipdtmpl[15];
  if (sp==255) sp = -999;
  return(sp);
}
