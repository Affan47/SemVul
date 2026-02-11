gxhbgn (char *fname) {
gaint xx,rc;
short bb[3];

  if (hferr) {
    printf ("Metafile error state is positive.\n");
    printf ("Disable Print before attempting an Enable Print.\n");
    return (0);
  }


  if (hflag) {
    printf ("Metafile already open\n");
    return(0);
  }

  hfile = fopen(fname,"wb");
  if (hfile==NULL) {
    printf ("Error opening meta file %s \n", fname);
    return (1);
  }


  if (bopt) {
    hbuff = (short *)malloc(sizeof(short)*buffsz);
    if (hbuff==NULL) {
      printf ("Unable to allocate memory for metafile operations.\n");
      fclose(hfile);
      return (1);
    }
    hpnt = hbuff;
    hend = hbuff+(buffsz-10L);
    bflag = 0;
  }


  bb[0] = -1;
  xx = (gaint)(xrsize*1000.0+0.5);
  if (xx<0) xx=0;
  if (xx>32760) xx=32760;
  bb[1] = xx;
  xx = (gaint)(yrsize*1000.0+0.5);
  if (xx<0) xx=0;
  if (xx>32760) xx=32760;
  bb[2] = xx;
  rc = gxhwri(bb, 3);
  if (rc) return (1);
  hpos = ftell(hfile);
  herr = 0;
  hpflg = 0;
  hferr = 0;
  hflag = 1;
  if (bopt) {
    printf ("File buffering enabled. ");
    printf ("Issue CLEAR command to start buffering.\n");
  }
  return (0);
}
