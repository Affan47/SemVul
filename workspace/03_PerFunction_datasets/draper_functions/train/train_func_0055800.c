gxpclab (gadouble xpos, gadouble ypos, gadouble rot, gaint ccol, struct gxcntr *pcntr) {
  gadouble x,y,w,h,csize,buff;
  gaint lablen,bcol,fcol,scol,swid;

  csize = pcntr->labsiz;
  lablen = strlen(clabel);
  bcol = gxqbck();
  h = csize*1.2;
  w = 0.2;
  gxchln (clabel,lablen,csize,&w);
  buff=h*0.05;
  x = xpos-(w/2.0);
  y = ypos-(h/2.0);
  scol = gxqclr();
  if (pcntr->labcol > -1) fcol = pcntr->labcol;
  else fcol = ccol;
  gxcolr (fcol);
  swid = gxqwid();


  if (pcntr->labwid > -1) gxwide(pcntr->labwid);
  if (pcntr->labwid == -999) {

     gxwide(12); gxcolr(bcol);
  }

  gxchpl (clabel,lablen,x,y,h,csize,0.0);
  if (pcntr->labwid == -999) {

    gxwide(1); gxcolr(fcol);
    gxchpl (clabel,lablen,x,y,h,csize,0.0);
  }
  gxmaskrec (x-buff, x+w+buff, y-buff, y+h+buff);
  gxcolr (scol);
  gxwide (swid);
}
