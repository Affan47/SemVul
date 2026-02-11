gxhfrm (gaint iact) {
short bb;
gaint rc,i;

  if (hflag) {
    fseek(hfile,hpos,0L);
    if (hpflg) {
      bb = -2;
      rc = gxhwri(&bb, 1);
      hpflg = 0;
      if (!rc) hpos = ftell(hfile);
    }
  }
  if (iact==2 && dbmode==0) {
    dbmode = 1;
    if (bopt==0) {
      hbuff = (short *)malloc(sizeof(short)*buffsz);
      if (hbuff==NULL) {
        printf ("Memory allocation error for metafile buffers.\n");
        herr = 1;
        pnt2 = 0;
        bufs2[0] = NULL;
      } else {
        pnt2 = 1;
        pntf = 1;
        bufs2[0] = hbuff;
      }
    }
  }
  if (iact!=2 && dbmode==1) {
    dbmode = 0;
    if (bopt==0) {
      for (i=0; i<pnt2; i++) free(bufs2[i]);
      pnt2 = 0;
    }
  }
  if (bopt==0) {
    if (dbmode) {
      if (pntf==0) {
        lens[pnt-1] = hpnt-hbuff;
        for (i=1; i<pnt2; i++) free(bufs2[i]);
        pntf = 1;
        pnt2 = 1;
        hbuff = bufs2[0];
        hpnt = hbuff;
        hend = hbuff+(buffsz-10L);
      } else {
        lens2[pnt2-1] = hpnt-hbuff;
        for (i=1; i<pnt; i++) free(bufs[i]);
        pntf = 0;
        pnt = 1;
        hbuff = bufs[0];
        hpnt = hbuff;
        hend = hbuff+(buffsz-10L);
      }
    } else {
      for (i=1; i<pnt; i++) {
        free(bufs[i]);
      }
      pnt = 1;
      hbuff = bufs[0];
      hpnt = hbuff;
      hend = hbuff+(buffsz-10L);
    }
    if (herr && bufs[0] && !dbmode) herr = 0;
  } else hpnt = hbuff;
}
